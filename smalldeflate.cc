#define SDEFL_IMPLEMENTATION

#include "shared.hh"
#include "sdefl.h"

std::vector<char> CompressData(const std::vector<char>& data)
{
    auto* s_sdefl = new sdefl();
    
    int bounds = sdefl_bound(data.size());
    auto compData = std::vector<char>(bounds);
    
    int length = sdeflate(s_sdefl, compData.data(), data.data(),
                          static_cast<int>(compData.size()), COMPRESSION_QUALITY_DEFLATE);
    
    free(s_sdefl);
    compData.resize(length);
    return compData;
}

int main(int argc, char** argv)
{
    return CompressOrDecompress(argc, argv);
}
