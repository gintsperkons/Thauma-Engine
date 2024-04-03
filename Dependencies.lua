VULKAN_SDK = os.getenv("VULKAN_SDK")
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Vendor/Libraries/GLFW/include"
IncludeDir["GLAD"] = "%{wks.location}/Vendor/Libraries/GLAD/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"


LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"