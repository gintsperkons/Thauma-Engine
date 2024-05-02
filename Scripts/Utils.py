import sys
import os
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines
sys.path.insert(0, Defines.pythonPath+"\\Lib\\site-packages")
import requests
import zipfile

def checkDirectory(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

def downloadFile(url, fileLocation,name):
    checkDirectory(os.path.dirname(fileLocation))
    r = requests.get(url, stream=True)
    with open(fileLocation+name, 'wb+') as f:
        for chunk in r.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)


def unzipFile(fileLocation, destinationFolder):
    with zipfile.ZipFile(fileLocation, 'r') as zip_ref:
        zip_ref.extractall(destinationFolder)
