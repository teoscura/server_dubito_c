#ifndef I_PACKET_H
#define I_PACKET_H

#include "../../defines/dint.hpp"

#include <vector>

using namespace dint;

class IPacket 
{
    public:
        virtual std::vector<u8>& unpack() = 0;
        virtual u32 conn() = 0;
        virtual ~IPacket() = 0;    
};

#endif