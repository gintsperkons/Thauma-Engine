import sys
import os
requiredPackages = ["requests"]
pythonBinary = os.getcwd()+"/Vendor/Binary/Python/python.exe"

PremakeURL = {
    "nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
    }
VulkanSDKURL = {
    "nt":"https://sdk.lunarg.com/sdk/download/1.3.290.0/windows/VulkanSDK-1.3.290.0-Installer.exe"
    }

projectPath = os.getcwd()
TempPath = projectPath+"/Vendor/Binary/Temp"
BinaryPath = "Vendor/Binary/"
