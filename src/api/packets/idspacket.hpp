#ifndef I_DSPACKET_H
#define I_DSPACKET_H

#include "ipacket.hpp"

#include "../../defines/dint.hpp"
#include <memory>

using namespace dint;

class IDsPacket
{
    public:
        virtual std::shared_ptr<IPacket> const serialize() = 0;
        virtual ~IDsPacket() = 0;
};

#endif