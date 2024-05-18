
import sys
import os
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines
import Utils


args = sys.argv
task = args[1]
environment = args[2]





if task == "SetupPython":
    import ValidatePythonPackages
    print("Validating Python Packages")
    ValidatePythonPackages.ValidatePythonPackages()

if task == "SetupPremake":
    import SetupWorkSpace
    print("Setting up workspace")
    SetupWorkSpace.SetupPremake(environment)

if task == "VulkanSDKSetup":
    vulkanInstallerUrl = "https://sdk.lunarg.com/sdk/download/1.3.280.0/windows/VulkanSDK-1.3.280.0-Installer.exe"
    vulkanPath = os.environ["VULKAN_SDK"]
    vulkanPath = ""
    if vulkanPath == "":
        if input("Install VulkanSDK Y|N ") != "y":
            print("VulkanSDK is required accept or install manually from https://vulkan.lunarg.com/sdk/home#windows")
        else:
            Utils.checkDirectory(Defines.TempPath)
            os.system(f'powershell.exe -Command "Invoke-WebRequest -Uri {  vulkanInstallerUrl } -OutFile { Defines.TempPath }/vulkanSDKinstaller.exe"')
            os.system(f".\\{Defines.TempPath}\\vulkanSDKinstaller.exe")