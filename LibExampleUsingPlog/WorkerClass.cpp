#include "WorkerClass.h"

#include <filesystem>
#include <thread>
#include <chrono>
#include <random>
#include <cstdio>

#include <plog/Log.h>

// PLOG related defines
#define PLOG_DEFAULT_SEVERITY plog::Severity::info
#define PLOG_SEVERITY_LOGGING_OFF plog::Severity::none // if severity is none, nothing will be logged. Even if init has been called, and not even the files would be created

// PLOG instance IDs
#define PLOG_DEBUG_LOGGING_INSTANCE 22811

#define PLOG_MAXNFILES 5
#define PLOG_DEBUG_LOGGING_FILESIZE_IN_BYTES 1024*1024*5 // 5 MB each

#define PLOG_LOCAL // A PLOG define, this forces our plog to be not-shared with any other instance of plog. See: https://github.com/SergiusTheBest/plog#share-log-instances-across-modules-exe-dll-so-dylib

#define NUMBER_OF_TIMES_TO_WRITE_LOG 5

#define RANDOM_MIN 1
#define RANDOM_MAX 10

CWorkerClass* CWorkerClass::m_pInstance{ nullptr };
std::mutex CWorkerClass::m_instanceMutexLock;

CWorkerClass* CWorkerClass::GetInstance()
{
	std::lock_guard<std::mutex> lock(m_instanceMutexLock);
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CWorkerClass();
	}
	return m_pInstance;
}

void CWorkerClass::InitRestOfLib(std::string sPlogFileName)
{
	m_sPlogFileName = sPlogFileName;

	std::string sBasePathEnv = "HOME";
	const char* cBasePath = std::getenv(sBasePathEnv.c_str());
	std::string sBasePath;
	if (cBasePath != nullptr)
	{
		sBasePath = std::string(cBasePath);
	}

	// create dir
	std::string sPathSubFolder(sBasePath + "/LogFileDir/");
	std::string sPath;

	if (std::filesystem::exists(sPathSubFolder) == false)
	{
		int resCode = mkdir(sPathSubFolder.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); // R=read, W=write, X=execute, U=user, GRP=group, OTH=other (i.e, this is chmod 755
		sPath = (resCode != errno && resCode != EEXIST) ? std::string(sPathSubFolder.begin(), sPathSubFolder.end()) : sBasePath;
	}
	else
	{
		sPath = std::string(sPathSubFolder.begin(), sPathSubFolder.end());
	}

	// set path
	m_sFinalPath = sPath + "/" + m_sPlogFileName + "_log.txt"; // prefix with log file name base.

	// init plogging
	plog::init<PLOG_DEBUG_LOGGING_INSTANCE>(PLOG_DEFAULT_SEVERITY, m_sFinalPath.c_str(), PLOG_DEBUG_LOGGING_FILESIZE_IN_BYTES, PLOG_MAXNFILES); // plog::init on NON-_WIN32 needs const char *

	// spawn thread to call work.
	std::thread threadHandle = std::thread(&CWorkerClass::DoWork, this);
	threadHandle.detach();
}

void CWorkerClass::DoWork()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(RANDOM_MIN, RANDOM_MAX);

	// Log something.
	for (int index = 0; index < NUMBER_OF_TIMES_TO_WRITE_LOG; index++)
	{
		std::string message = 
			"Hello, my name is "
			+ m_sPlogFileName
			+ ". My Id is "
			+ std::to_string(PLOG_DEBUG_LOGGING_INSTANCE)
			+ " and i will log to file "
			+ m_sFinalPath
			+ " "
			+ std::to_string(NUMBER_OF_TIMES_TO_WRITE_LOG)
			+ " times. This is time #"
			+ std::to_string(index);

		LOGI_(PLOG_DEBUG_LOGGING_INSTANCE) << message;
		message += "\n";
		printf(message.c_str());

		// Sleep for a random amount of time.
		std::this_thread::sleep_for(std::chrono::milliseconds(distr(eng) * 100));
	}
}
