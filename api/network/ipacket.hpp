#ifndef I_PACKET_H
#define I_PACKET_H

#include "../../defines/dint.hpp"

#include <vector>

using namespace dint;

class IPacket 
{
    public:
        virtual std::vector<u8>& unpack();
        virtual ~IPacket() = default;
};

#endif