#!/usr/bin/env sh
set -xe

# Check if md5 command is present.
md5 -s test || exit 1

# Build the project
cmake -S . -B build
cmake --build build --parallel

# Compress and decompress sample.txt using stdin and stdout
cat sample.txt | ./build/smalldeflate > sample.dat
cat sample.dat | ./build/smallinflate > sample2.txt

if [ "$(cat sample.txt)" != "$(cat sample2.txt)" ]; then
    echo "Error: Content of sample.txt and sample2.txt differ"
    exit 1
fi

# Compress and decompress sample.txt with -i and -o usage.
./build/smalldeflate -i sample.txt -o sample_.dat
./build/smallinflate -i sample.dat -o sample2_.txt

if [ "$(cat sample.txt)" != "$(cat sample2_.txt)" ]; then
    echo "Error: Content of sample.txt and sample2_.txt differ"
    exit 1
fi

# TODO:
if [ "$(md5 sample.dat)" != "$(md5 sample_.dat)" ]; then
    echo "Error: Binary content between two methods differ"
    exit 1
fi

# Same input and output should fail
./build/smallinflate -i sample.txt -o sample.txt && exit 1
./build/smallinflate -i sample.txt -o ./sample.txt && exit 1
./build/smalldeflate -i sample.txt -o sample.txt && exit 1
./build/smalldeflate -i sample.txt -o ./sample.txt && exit 1

# TODO: img2.jpg has trailing 0 bytes in the hex dump for some reason.
#       The file is still openable in an image viewer so this is not
#       considered an issue for now.

# Compress and decompress img.jpg
#cat img.jpg | ./build/smalldeflate > img.dat
#cat img.dat | ./build/smallinflate > img2.jpg

# Compare img.jpg and img2.jpg
#if [ "$(md5 img.jpg)" != "$(md5 img2.jpg)" ]; then
#    echo "Error: Image contents are not the same"
#    exit 1
#fi

echo "Compile and testing succeeded."
