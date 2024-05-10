import sys
import os
requiredPackages = ["requests"]
pythonExecutable = sys.executable
pythonPath = sys.executable.replace('python.exe', '')
pipPath = pythonPath+"Lib\\site-packages\\pip"

projectPath = os.getcwd()
TempPath = projectPath+"/Vendor/Binaries/Temp"

externalItemsPath = "Vendor/Binaries/"
