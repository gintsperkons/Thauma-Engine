import sys
import os
requiredPackages = ["requests"]
pythonBinary = os.getcwd()+"/Vendor/Binary/Python/python.exe"

PremakeURL = {
    "nt":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip",
    "posix":"https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz"
    }
VulkanSDKURL = {
    "nt":"https://sdk.lunarg.com/sdk/download/1.3.290.0/windows/VulkanSDK-1.3.290.0-Installer.exe",
    "posix":"https://sdk.lunarg.com/sdk/download/1.3.290.0/linux/vulkansdk-linux-x86_64-1.3.290.0.tar.xz"
    }

projectPath = os.getcwd()
TempPath = projectPath+"/Vendor/Binary/Temp"
BinaryPath = "Vendor/Binary/"

premakeExtensions =  {
    "nt":".exe",
    "posix":""
}

premakeArchiveExtensions =  {
    "nt":".zip",
    "posix":".tar.gz"
}