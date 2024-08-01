#!/bin/bash

set -euo pipefail

# Change to the directory where the script is located
cd "$(dirname "$0")"

# Create the Compiled directory if it doesn't exist
mkdir -p Compiled

echo "---Compiling shaders---"

# Iterate over each .vert and .frag file in Raw directory
find Raw -type f \( -name '*.vert' -o -name '*.frag' \) | while read -r file; do
    # Set the relative path
    relativePath="${file#Raw/}"

    # Construct the output path
    outputRelativePath="${relativePath/Raw/Compiled}"
    
    # Change .vert to -vert.spv and .frag to -frag.spv
    outputRelativePath="${outputRelativePath/.vert/-vert.spv}"
    outputRelativePath="${outputRelativePath/.frag/-frag.spv}"

    echo "$relativePath --^> $outputRelativePath"

    # Compile the shader using glslc
    "$VULKAN_SDK/bin/glslc" "$file" -o "$outputRelativePath"
done

echo "---Done---"
    