#include "LibLoader.h"
#include <iostream>

const std::string CLibLoader::m_sLibBaseName = "libLibExampleUsingPlog";

#define NULLPTRCHECK(fn) if ((fn)==nullptr) throw true // used during function pointer fetching

CLibLoader::CLibLoader(
	const unsigned int& driverIndex) :
	m_uiDriverLoaderIndex(driverIndex)
{
}

CLibLoader::~CLibLoader()
{
	Unload();
}

bool CLibLoader::Load()
{
	try
	{		
		m_sLibName = "./" + m_sLibBaseName + "_" + std::to_string(m_uiDriverLoaderIndex) + ".so";
		std::string sFinalName(m_sLibName.begin(), m_sLibName.end());
		const char* pSharedObjectName = sFinalName.c_str();

		m_loadedLibHandle = dlopen(pSharedObjectName, RTLD_NOW);

		if (m_loadedLibHandle == nullptr)
		{
			std::string lastError = dlerror();
			std::cout << lastError << "\n";
			std::cout << "Failed to load dynamic library: " << sFinalName << "\n";
			return false;
		}

		// set isNullptrCheck
		CheckNotNullptr isNullptrCheck;

		// assign driver methods to our function pointers
		NULLPTRCHECK(m_pfn_init = (LPFUN_init)dlsym(m_loadedLibHandle, "lib_init"));
		return true;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception caught: " << ex.what();
		return false;
	}
	catch (const std::string& ex)
	{
		std::cout << "Exception caught: " << ex;
		return false;
	}
	catch (...)
	{
		std::cout << "Unknown Exception caught";
		return false;
	}
}

void CLibLoader::Unload()
{
}

bool CLibLoader::InitializeLib()
{
	std::string sLibName = m_sLibName;

	// Strip any file extension types.
	size_t dotIndex = sLibName.find_last_of('.');
	if (dotIndex > 0)
	{
		sLibName = sLibName.substr(0, dotIndex);
	}

	// This will call the init function and get the lib to start using plog.
	unsigned int resultCode = m_pfn_init(sLibName.c_str(), (unsigned int)sLibName.length());
	if (resultCode != 0)
	{
		std::cout << "Driver: " << sLibName << " init call failed, code: " << resultCode;
		return false;
	}

	return true;
}

