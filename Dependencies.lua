VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Libraries/GLFW/include"
IncludeDir["GLM"] = "%{wks.location}/Vendor/Libraries/GLM"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {} 
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"