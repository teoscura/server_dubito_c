#ifndef DSPACKET_H
#define DSPACKET_H

#include "../api/packets/idspacket.hpp"

#include "../api/network/itcpsocket.hpp"
#include <memory>

class DsPacket : public IDsPacket
{
    protected:
        Connection mrecipient;
        DsPacket(Connection recipient);
    public:
        virtual std::shared_ptr<IPacket> const serialize() override = 0;
        virtual ~DsPacket() override = 0;
};

#endif