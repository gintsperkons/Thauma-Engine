
import sys
import os
current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(current_dir))
import Defines


args = sys.argv
environment = args[1]


import ValidatePythonPackages
print("Validating Python Packages")
ValidatePythonPackages.ValidatePythonPackages()
import SetupWorkSpace
print("Setting up workspace")
SetupWorkSpace.SetupPremake(environment)