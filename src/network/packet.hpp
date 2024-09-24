#ifndef PACKET_H 
#define PACKET_H

#include "../../api/network/ipacket.hpp"

class Packet : public IPacket 
{
    private:
        std::vector<u8> mdata;
    public:
        Packet(std::vector<u8> data);
        std::vector<u8>& unpack() override;
};

#endif