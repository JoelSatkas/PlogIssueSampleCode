#pragma once

#include <dlfcn.h>
#include <string>

typedef unsigned int(*LPFUN_init)(const char*, unsigned int);

/// <summary>
/// Little helper class to throw exceptions upon failure to assign a dll method
/// When we use this during assignment, we don't need the constant == nullptr in InitiateTests()
/// </summary>
class CheckNotNullptr
{
public:
	CheckNotNullptr() {};
	void operator=(const void* p) { if (p == nullptr) throw true; };
};

class CLibLoader
{
public:

	/// <summary>
	/// Constructor 
	/// </summary>
	CLibLoader(const unsigned int& driverIndex);

	/// <summary>
	/// Destructor
	/// </summary>
	~CLibLoader();

	/// <summary>
	/// Loads the dynamic library associated with this loader.
	/// </summary>
	/// <returns>True if loaded, False otherwise</returns>
	bool Load();

	/// <summary>
	/// Unloads the dynamic library.
	/// </summary>
	void Unload();

	/// <summary>
	/// Initializes lib
	/// </summary>
	/// <returns>True if successful, false otherwise.</returns>
	bool InitializeLib();



	static const std::string m_sLibBaseName;

private:

	/// <summary>
	/// The name of the lib that this loader will load.
	/// </summary>
	std::string m_sLibName = "";

	/// <summary>
	/// The lib index this library loader will be assigned, passed into the constructor and will determine which library file to load.
	/// </summary>
	const unsigned int m_uiDriverLoaderIndex;

	/// <summary>
	/// Handle to the DLL/.so, used for registering functions/unloading
	/// </summary>
	 void* m_loadedLibHandle;

	 LPFUN_init m_pfn_init;


};