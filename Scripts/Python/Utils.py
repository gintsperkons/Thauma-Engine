import sys
import Defines
def IsPackageInstalled(package):
    try:
        __import__(package)
    except ImportError:
        return False
    return True

def InstallPackage(package):
    import subprocess
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

def checkFolder(path):
    import os
    if not os.path.exists(path):
        os.makedirs(path)

def formatAmount(amount):
    if amount < 1024:
        return str(round(amount,2)) + " B"
    elif amount < 1024*1024:
        return str(round(amount/1024,2)) + " KB"
    elif amount < 1024*1024*1024:
        return str(round(amount/(1024*1024),2)) + " MB"
    else:
        return str(round(amount/(1024*1024*1024),2)) + " GB"

def DownloadFile(url, path):
    import os
    checkFolder(os.path.dirname(path))
    import requests
    r = requests.get(url, stream=True)
    with open(path, "wb") as f:
        print("Downloading %s" % path)
        response = requests.get(url, stream=True)
        total_length = response.headers.get('content-length')

        if total_length is None: # no content length header
            f.write(response.content)
        else:
            dl = 0
            total_length = int(total_length)
            for data in response.iter_content(chunk_size=4096):
                dl += len(data)
                f.write(data)
                done = int(50 * dl / total_length)
                sys.stdout.write("\r[%s%s] %s/%s %s" % ('=' * done, ' ' * (50-done),formatAmount(dl),formatAmount(total_length),' '*5) )    
                sys.stdout.flush()

def ExtractZip(zipPath, extractPath):
    import zipfile
    import os
    checkFolder(extractPath)
    with zipfile.ZipFile(zipPath, 'r') as zip_ref:
        zip_ref.extractall(extractPath)
def ReloadPremake(enviroment = "vs2022"):
    import os
    print(os.getcwd()+"/"+Defines.BinaryPath+"Premake/premake5"+Defines.premakeExtensions[os.name]+" "+enviroment)
    os.system(os.getcwd()+"/"+Defines.BinaryPath+"Premake/premake5"+Defines.premakeExtensions[os.name]+" "+enviroment)

def ExtractTar(tarPath, extractPath):
    import tarfile
    import os
    checkFolder(extractPath)
    with tarfile.open(tarPath, 'r') as tar_ref:
        tar_ref.extractall(extractPath)

def Extract(archivePath, extractPath):
    import os
    if archivePath.endswith(".zip"):
        ExtractZip(archivePath, extractPath)
    elif archivePath.endswith(".tar.gz"):
        ExtractTar(archivePath, extractPath)
    else:
        print("Archive format not supported")
        return  

def LaunchVS():
    import os
    for root, dirs, files in os.walk(Defines.projectPath):
        for file in files:
            if file.endswith(".sln"):
                os.system("start "+os.path.join(root, file))
    return