#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <unistd.h>

constexpr size_t COMPRESSION_QUALITY_DEFLATE = 8;
constexpr size_t MAX_DECOMPRESSION_SIZE = 1024*1024*1024;

using ByteVec = std::vector<char>;

template <std::ostream& S>
void PrintHelp(const std::string_view& toolName)
{
    S << "Usage: cat file | " << toolName << " > output\n\n";
    S << "Note: Compression level 8 is used. The raylib default" << std::endl;
}

#ifdef SINFL_IMPLEMENTATION
ByteVec DecompressData(const ByteVec& compData);
#else
ByteVec CompressData(const ByteVec& data);
#endif

int CompressOrDecompress()
{
    std::vector<char> buffer;

    char ch;
    while (std::cin.get(ch)) {
        buffer.emplace_back(ch);
    }

    if (buffer.empty()) {
#ifdef SINFL_IMPLEMENTATION
        PrintHelp<std::cerr>("smallinflate");
#else
        PrintHelp<std::cerr>("smalldeflate");
#endif
        return EXIT_FAILURE;
    }

    if (!std::cin.eof()) {
        std::cerr << "Error reading from stdin" << std::endl;
        return EXIT_FAILURE;
    }

#ifdef SINFL_IMPLEMENTATION
    const ByteVec data = DecompressData(buffer);
#else
    const ByteVec data = CompressData(buffer);
#endif

    std::cout.write(reinterpret_cast<const char*>(data.data()), data.size());
    return EXIT_SUCCESS;
}
