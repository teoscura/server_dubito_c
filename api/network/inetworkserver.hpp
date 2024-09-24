#ifndef I_NETWORKSERVER_H
#define I_NETWORKSERVER_H

#include "../../defines/dint.hpp"
#include "ipacket.hpp"
#include <vector>

using namespace dint;

class INetworkServer
{
    public:
        virtual void start(u32 port);
        virtual void send(std::vector<u8> data, u32 recipient);
        virtual std::vector<IPacket> incoming_packets();
        virtual ~INetworkServer();   
};

#endif