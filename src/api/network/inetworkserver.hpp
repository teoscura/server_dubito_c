#ifndef I_NETWORKSERVER_H
#define I_NETWORKSERVER_H

#include "../../defines/dint.hpp"
#include "../packets/ipacket.hpp"
#include <memory>
#include <vector>

using namespace dint;

class INetworkServer
{
    public:
        virtual std::vector<std::shared_ptr<IPacket>> p_incoming_packets() = 0;
        virtual void send(std::vector<u8> data, u32 recipient) = 0;
        virtual ~INetworkServer() = 0;   
};

#endif