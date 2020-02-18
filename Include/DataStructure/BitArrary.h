#pragma once
#include "Common/GlobalVariables.h"
#include <array>

class BitArray
{
    static const JSint32 MAX_NUM_OF_BUCKET = 32;
    static const JSint8 NUM_OF_BITS = 64;
    static const JSint64 ONE_IN_64_BIT = 1;
public:
    BitArray() { for (JSint32 i = 0; i < MAX_NUM_OF_BUCKET; ++i)    m_BitArray[i] = 0; }
    void SetKBitToOne(JSint32 index) { m_BitArray[index / NUM_OF_BITS] |= ONE_IN_64_BIT << (index % NUM_OF_BITS); }
    void SetKBitToZero(JSint32 index) { m_BitArray[index / NUM_OF_BITS] &= ~(ONE_IN_64_BIT << (index % NUM_OF_BITS)); }
    void ToggleKBit(JSint32 index) { m_BitArray[index / NUM_OF_BITS] ^= ONE_IN_64_BIT << (index % NUM_OF_BITS); }
    bool IsCurrentIndexIsSet(JSint32 index) { return m_BitArray[index / NUM_OF_BITS] & (ONE_IN_64_BIT << (index % NUM_OF_BITS)); }
private:
    std::array<JSint64, MAX_NUM_OF_BUCKET> m_BitArray;
};
