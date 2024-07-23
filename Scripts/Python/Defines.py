import sys
import os
requiredPackages = ["requests"]
pythonBinary = os.getcwd()+"/Vendor/Binary/Python/python.exe"

PremakeURL = {
    "nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
    }

projectPath = os.getcwd()
TempPath = projectPath+"/Vendor/Binary/Temp"
BinaryPath = "Vendor/Binary/"
