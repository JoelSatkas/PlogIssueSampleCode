#include "API_Layer_lib.h"
#include "WorkerClass.h"

#include <string>

__attribute__((visibility("default"))) unsigned int lib_init(const char* pcNameBase, unsigned int uiCharrArraySize)
{
	// parse string from input, in particular way so that empty string is correctly interpreted
	std::string sName;
	std::string sBaseName = "LibLog";

	if (pcNameBase == nullptr ||
		uiCharrArraySize == 0 || // if nullptr or size 0, the input is an empty string, which is valid!
		(uiCharrArraySize == 1 && pcNameBase[0] == '\0')) // this indicates an empty string
	{
		sName = std::string("");
	}
	else
	{
		// Don't use the null character in the input, it will cause issues down the line, when we suffix the log file name
		unsigned int nChars = uiCharrArraySize;
		if (pcNameBase[uiCharrArraySize - 1] == '\0')
		{
			nChars--;
		}
		sName = std::string(pcNameBase, nChars);
	}

	// set log base name, either to the input, or to whatever was already set in sBaseName upon dll load
	if (!sName.empty())
	{
		sBaseName = std::string(sName.begin(), sName.end()); // sBaseName is often set upon driver dll load, so we need to overwrite it
	}

	CWorkerClass::GetInstance()->InitRestOfLib(sBaseName);

	return 0;
}


