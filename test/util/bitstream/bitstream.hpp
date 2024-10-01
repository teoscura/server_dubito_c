#ifndef BITSTREAM_H
#define BITSTREAM_H

#include "../../defines/dint.hpp"

#include <bit>
#include <vector>

using namespace dint;

class BitStream
{
    private:
        std::vector<u8> mdata;
    public:
        BitStream() = default;
        template<typename A>
        void operator<<(A a);
        const std::vector<u8>& read() const { return mdata; };
        ~BitStream() = default;
};

template<typename A>
void BitStream::operator<<(A a)
{
    static_assert( std::is_trivially_copyable<A>::value,\
                   "Not BitStreamable.");
    u32 t = sizeof(A);
    u8* ptr = reinterpret_cast<u8*>(&a);
    u8 tmp;
    for(auto i = 0 ; i<t ; i++)
    {
        mdata.push_back(ptr[i]);
    }    
}

#endif