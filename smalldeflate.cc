#define SDEFL_IMPLEMENTATION
#include <memory>

#include "shared.hh"
#include "sdefl.h"

ByteVec CompressData(const ByteVec& data)
{
    auto s_sdefl = std::make_unique<sdefl>();
    
    int bounds = sdefl_bound(data.size());
    ByteVec compData = ByteVec(bounds);
    
    int length = sdeflate(s_sdefl.get(), compData.data(), data.data(),
                          static_cast<int>(compData.size()), COMPRESSION_QUALITY_DEFLATE);

    compData.resize(length);
    return compData;
}

int main()
{
    return CompressOrDecompress();
}
