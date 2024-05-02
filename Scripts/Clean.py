
import sys
import os
import shutil
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines

fileExtensions = [".pyc",".pyo",".sln",".vcxproj",".vcxproj.filters",".vcxproj.user"]

for root, dirs, files in os.walk(Defines.projectPath):
    for file in files:
        for extension in fileExtensions:
            if file.endswith(extension):
                os.remove(os.path.join(root, file))
    for dir in dirs:
        print(dir)
        if dir == "__pycache__":
            shutil.rmtree(os.path.join(root, dir))

shutil.rmtree(Defines.projectPath+"\\Binaries")