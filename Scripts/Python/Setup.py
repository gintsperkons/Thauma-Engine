import sys
import os
import Defines
import Utils

def GetDependencies():
    for module in Defines.requiredPackages:
        if not Utils.IsPackageInstalled(module):
            Utils.InstallPackage(module)
    return

def SetupPremake(enviroment):
    if not os.path.exists(Defines.BinaryPath+"/Premake/premake5"+Defines.premakeExtensions[os.name]):
        Utils.DownloadFile(Defines.PremakeURL[os.name],Defines.TempPath+"/premake"+Defines.premakeArchiveExtensions[os.name])
        Utils.Extract(Defines.TempPath+"/premake"+Defines.premakeArchiveExtensions[os.name],Defines.BinaryPath+"/Premake")
    Utils.ReloadPremake(enviroment)

def CheckVulkanSDK():   
    if os.environ.get("VULKAN_SDK") == None:
        print("Vulkan SDK not found")
        print("Please download and install the Vulkan SDK from https://vulkan.lunarg.com")
    else:
        print("Vulkan SDK found at "+os.environ.get("VULKAN_SDK")) 

#vs2022 open
if __name__ == "__main__":
    args = sys.argv #vs2022 open yes
    GetDependencies()

    CheckVulkanSDK()
    #premake
    if args[1] == '':
        print("Please provide the enviroment for premake")
    SetupPremake(args[1])
    if len(args) > 2:
        if args[2] == "open":
            Utils.LaunchVS()
    




