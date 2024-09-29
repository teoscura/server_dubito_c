#ifndef DSPACKET_H
#define DSPACKET_H

#include "../api/packets/idspacket.hpp"

#include "../api/network/itcpsocket.hpp"

class DsPacket : public IDsPacket
{
    protected:
        Connection mrecipient;
        DsPacket(Connection recipient);
    public:
        virtual IPacket const serialize() override = 0;
        virtual ~DsPacket() override = 0;
};

#endif