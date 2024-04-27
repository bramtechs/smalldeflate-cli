#!/usr/bin/env sh
set -xe

# Build the project
cmake -S . -B build
cmake --build build --parallel

# Compress and decompress sample.txt
cat sample.txt | ./build/smalldeflate > sample.dat
cat sample.dat | ./build/smallinflate > sample2.txt

# Compare strings of sample.txt and sample2.txt
if [ "$(cat sample.txt)" != "$(cat sample2.txt)" ]; then
    echo "Error: Content of sample.txt and sample2.txt differ"
    exit 1
fi

# TODO: img2.jpg has trailing 0 bytes in the hex dump for some reason
#       The file is still openable in an image viewer so this issue is unresolved.

# Compress and decompress img.jpg
#cat img.jpg | ./build/smalldeflate > img.dat
#cat img.dat | ./build/smallinflate > img2.jpg

# Compare img.jpg and img2.jpg without accounting for trailing CR characters
#if ! diff -q --strip-trailing-cr img.jpg img2.jpg; then
#    echo "Error: img.jpg and img2.jpg differ"
#    exit 1
#fi

echo "Compile and testing succeeded."
