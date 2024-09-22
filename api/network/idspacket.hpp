#ifndef I_DSPACKET_H
#define I_DSPACKET_H

#include "ipacket.hpp"

#include "../../defines/dint.hpp"

using namespace dint;

class IDsPacket
{
    public:
        virtual IPacket serialize();
        virtual ~IDsPacket() = default;
};

#endif