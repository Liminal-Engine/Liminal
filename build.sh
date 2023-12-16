#!/bin/bash

if [ -z "$1" ] || { [ "$1" != "Debug" ] && [ "$1" != "Release" ] && [ "$1" != "Continue"]; }; then
    echo "Usage: $0 <Release|Debug|Continue>"
    exit 1
fi

if [ "$1" == "Continue" ]; then
    cd $(dirname $0)/build
    cmake --build .
else
    cd $(dirname $0)
    rm -rf build
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=$1 ..
    cmake --build .
fi

exit 0
