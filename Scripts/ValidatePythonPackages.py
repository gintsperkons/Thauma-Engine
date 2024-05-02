import sys
import os
import importlib
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines
sys.path.insert(0, Defines.pythonPath+"\\Lib\\site-packages")

print(sys.path)
def InstallPythonPackage(packageName):
    os.system(f'{Defines.pythonExecutable} {Defines.pipPath} install {packageName}')

def ValidatePythonPackages():
    for package in Defines.requiredPackages:
        try:
            importlib.import_module(package)
            print(f'{package} installed')
        except ImportError:
            print(f'{package} not installed installing...')
            InstallPythonPackage(package)

if __name__ == '__main__':
    ValidatePythonPackages()