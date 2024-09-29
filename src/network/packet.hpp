#ifndef PACKET_H 
#define PACKET_H

#include "../api/network/ipacket.hpp"
#include "../api/network/itcpsocket.hpp"

class Packet : public IPacket 
{
    private:
        std::vector<u8> mdata;
        u32 mconn;
    public:
        Packet(u32 conn, std::vector<u8> data);
        std::vector<u8>& unpack() override;
        u32 conn() override;
        ~Packet() = default;
};

#endif