#! /bin/bash

sudo apt install -y \
g++ \
vulkan-tools \
libvulkan-dev \
vulkan-validationlayers-dev \
spirv-tools \
libglfw3-dev \
libxxf86vm-dev \
libxi-dev
firefox https://github.com/google/shaderc/blob/main/downloads.md

echo "DOWNLOAD YOUR NVIDIA GPU DRIVER HERE : https://www.nvidia.fr/Download/index.aspx?lang=fr"

echo "ALSO DOWNLOAD CUDA TOOLKIT HERE : https://developer.nvidia.com/cuda-dow-nloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=deb_network"
