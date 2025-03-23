#! /bin/bash

sudo apt install -y \
g++ \
vulkan-tools \
libvulkan-dev \
vulkan-validationlayers-dev \ (ou sudo apt install vulkan-validationlayers si vulkan-validationlayers-dev pas trouvé dans les dépots)
spirv-tools \
libglfw3-dev \
libxxf86vm-dev \
libxi-dev
firefox https://github.com/google/shaderc/blob/main/downloads.md --> Two popular shader compilers are Khronos Group's glslangValidator and Google's glslc. The latter has a familiar GCC- and Clang-like usage, so we'll go with that: on Ubuntu, download Google's unofficial binaries and copy glslc to your /usr/local/bin. Note you may need to sudo depending on your permissions. On Fedora use sudo dnf install glslc, while on Arch Linux run sudo pacman -S shaderc. To test, run glslc and it should rightfully complain we didn't pass any shaders to compile:
glslc: error: no input files

also install cmake

echo "DOWNLOAD YOUR NVIDIA GPU DRIVER HERE : https://www.nvidia.fr/Download/index.aspx?lang=fr"

echo "ALSO DOWNLOAD CUDA TOOLKIT HERE : https://developer.nvidia.com/cuda-dow-nloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=deb_network"