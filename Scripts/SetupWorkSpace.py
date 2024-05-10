import sys
import os
import shutil
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines
import Utils

def SetupPremake(environment = "vs2022"):
    url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
    archiveName = "premake.zip"
    fileName = "premake5.exe"
    
    location = Defines.projectPath +"\\" + Defines.externalItemsPath + "Premake\\"
    if os.path.exists(location+fileName):
        print("Premake already setup")
    else:
        print("Downloding Premake")
        Utils.checkDirectory(location+"Temp\\")
        Utils.downloadFile(url,location,"Temp\\"+archiveName)
        print("Unziping Premake")
        Utils.unzipFile(location+"Temp\\"+archiveName,location+"Temp\\")
        print("Removing Unwanted files")
        shutil.move(location+"Temp\\"+fileName,location+"\\"+fileName)
        shutil.rmtree(location+"Temp\\")
        print("Premake setup complete")
    os.system(f"{location+fileName} {environment}")


if __name__ == '__main__':
    SetupPremake()