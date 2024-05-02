import sys
import os
import shutil
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines
import Utils

def SetupPremake():
    url = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip"
    location = Defines.projectPath +"\\" + Defines.externalItemsPath + "Premake\\"
    if os.path.exists(location+"premake5.exe"):
        print("Premake already setup")
    else:
        print("Downloding Premake")
        Utils.checkDirectory(location+"Temp\\")
        Utils.downloadFile(url,location,"Temp\\premake.zip")
        print("Unziping Premake")
        Utils.unzipFile(location+"Temp\\premake.zip",location+"Temp\\")
        print("Removing Unwanted files")
        shutil.move(location+"Temp\\premake5.exe",location+"\\premake5.exe")
        shutil.rmtree(location+"Temp\\")
        print("Premake setup complete")
    os.system(f"{location+'premake5.exe'} vs2022")


if __name__ == '__main__':
    SetupPremake()