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
    if os.name == "nt":
        if not os.path.exists(Defines.BinaryPath+"/Premake/premake5.exe"):
            Utils.DownloadFile(Defines.PremakeURL[os.name],Defines.TempPath+"/premake.zip")
            Utils.ExtractZip(Defines.TempPath+"/premake.zip",Defines.BinaryPath+"/Premake")
        Utils.ReloadPremake(enviroment)

#vs2022 open
if __name__ == "__main__":
    args = sys.argv #vs2022 open yes
    GetDependencies()
    if args[1] == '':
        print("Please provide the enviroment for premake")
        exit()
    SetupPremake(args[1])
    if len(args) > 2:
        if args[2] == "open":
            Utils.LaunchVS()
    




