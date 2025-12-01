#!/bin/bash

cd "$(dirname "$0")"

/usr/local/bin/glslc ./triangle.vert -o triangle.vert.spv
/usr/local/bin/glslc ./triangle.frag -o triangle.frag.spv