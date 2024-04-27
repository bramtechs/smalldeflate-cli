#define SINFL_IMPLEMENTATION

#include "shared.hh"
#include "sinfl.h"

ByteVec DecompressData(const ByteVec& compData)
{
    ByteVec data = ByteVec(MAX_DECOMPRESSION_SIZE);
    int length = sinflate(data.data(), MAX_DECOMPRESSION_SIZE, compData.data(), compData.size());
    data.resize(length);
    return data;
}

int main()
{
    return CompressOrDecompress();
}
