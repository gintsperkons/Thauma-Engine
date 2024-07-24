local os = require("os")
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Library/GLFW/include"
IncludeDir["GLM"] = "%{wks.location}/Vendor/Library/GLM"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {} 

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1"