if not exist Compiled mkdir Compiled
%VULKAN_SDK%/bin/glslc.exe Raw/base.vert -o Compiled/base-vert.spv
%VULKAN_SDK%/bin/glslc.exe Raw/base.frag -o Compiled/base-frag.spv

