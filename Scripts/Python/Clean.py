
import sys
import os
import shutil
import Defines

fileExtensions = [".pyc",".pyo",".sln",".vcxproj",".vcxproj.filters",".vcxproj.user","Makefile"]
folderNames = ["__pycache__","Binaries",".vs"]

for root, dirs, files in os.walk(Defines.projectPath):
    for file in files:
        for extension in fileExtensions:
            if file.endswith(extension):
                os.remove(os.path.join(root, file))
                print("Removed: " + os.path.join(root, file))
    for dir in dirs:
        if dir in folderNames:
            shutil.rmtree(os.path.join(root, dir))
            print("Removed: " + os.path.join(root, dir))
