# PlogIssueSampleCode
 Project containing the "minimum" needed to reproduce github issue with shared log files

# You will need:
1. Visual Studio 2022 with c++ linuex development tools packages installed.
2. A real local or virtual linux machine to compile and run the project on.
3. Git and related software of choice.

# Running step
1. In visual studio, open the solution file in "PlogIssueSampleCode\libRunner\"
2. The VS settings are configured to use my own linux VM, config the setting for your own linux machine, changing the ip address, user name and password.
3. The lib example is already compiled and present in this repo but if you need to recompile it again:
	1. Rebuild the project.
	2. Find the .so file in your linux machine.
	3. Use the script at https://github.com/JoelSatkas/UniqueFileDuplicator to create 30 instances of the .so. Uses node js, dont forget to update the json file with the name of the file.
	4. Previouse step can be done on windows or linux machine, then move these new libs to the repo and replace the current libs there.
4. Rebuild the lib runner, this will copy the libs to the linux machine again.
5. Run and debug in VS. The log file will be made in HOME/LogFileDir/ 

# Notes:
This is a quick and dirty reprduction of what seems to be a plog issue? Although in this example i find a new one and that is that logging to a plog instance
will make multiple lines appear in the log file. I dont get this for my real project but my real project uses a lot more mutex locking and is of higher quality 
so could be a mistake on my part but the fprint in the console will not duplicate the lines like plog does. Could also be im initing it wrong.

Anyway, the 'PLOG_LOCAL' is defined but they all use the same log location even though they say in the logger they are trying to log to a different file.