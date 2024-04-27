#define SDEFL_IMPLEMENTATION

#include "shared.hh"
#include "sdefl.h"

ByteVec CompressData(const ByteVec& data)
{
    sdefl* s_sdefl = new sdefl();
    
    int bounds = sdefl_bound(data.size());
    ByteVec compData = ByteVec(bounds);
    
    int length = sdeflate(s_sdefl, compData.data(), data.data(),
                          static_cast<int>(compData.size()), COMPRESSION_QUALITY_DEFLATE);
    
    free(s_sdefl);
    compData.resize(length);
    return compData;
}

int main()
{
    return CompressOrDecompress();
}
