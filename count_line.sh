#!/bin/bash

# Find all .cpp, .hpp, .c, .h files in the current directory and its subdirectories except build directory
files=$(find . -type d -name "build" -prune -o -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -print)

total_lines=0

# Count the lines in each file
for file in $files; do
    lines=$(wc -l < "$file")
    total_lines=$((total_lines + lines))
done

echo "Total lines: $total_lines"
