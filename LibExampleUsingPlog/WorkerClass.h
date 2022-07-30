#pragma once
#include <string>
#include <mutex>

class CWorkerClass
{
public:

	/// <summary>
	/// Singletons should not be cloneable.
	/// </summary>
	/// <param name="other"></param>
	CWorkerClass(CWorkerClass& other) = delete;

	/// <summary>
	/// Singletons should not be assignable.
	/// </summary>
	/// <param name=""></param>
	void operator=(const CWorkerClass&) = delete;

	/// <summary>
	/// Returns instance 
	/// </summary>
	/// <returns></returns>
	static CWorkerClass* GetInstance();

	/// <summary>
	/// Only exposed function to simulate creating the rest of the lib and creating a chain or reaction.
	/// </summary>
	/// <param name="sPlogFileName">The name of the file plog will use.</param>
	void InitRestOfLib(std::string sPlogFileName);

private:

	/// <summary>
	/// Private constructor.
	/// </summary>
	CWorkerClass() {};

	/// <summary>
	/// Private destructor.
	/// </summary>
	~CWorkerClass() {};

	/// <summary>
	/// A short function that the thread will run in to simulate the lib having a mind of its own and doing work.
	/// </summary>
	void DoWork();

	/// <summary>
	/// Pointer to singleton instance (singleton for this copy of the DLL, multiple DLLs can still be loaded)
	/// </summary>
	static CWorkerClass* m_pInstance;

	/// <summary>
	/// Mutex for protecting instance access
	/// </summary>
	static std::mutex m_instanceMutexLock;

	/// <summary>
	/// The base name of the log file.
	/// </summary>
	std::string m_sPlogFileName = "";

	/// <summary>
	/// The final path location to the log file.
	/// </summary>
	std::string m_sFinalPath = "";
};