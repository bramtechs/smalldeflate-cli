#define SINFL_IMPLEMENTATION

#include "shared.hh"
#include "sinfl.h"

std::vector<char> DecompressData(const std::vector<char>& compData)
{
    auto data = std::vector<char>(MAX_DECOMPRESSION_SIZE);
    const int length = sinflate(data.data(), MAX_DECOMPRESSION_SIZE,
                                compData.data(), static_cast<int>(compData.size()));
    data.resize(length);
    return data;
}

int main(int argc, char** argv)
{
    return CompressOrDecompress(argc, argv);
}
