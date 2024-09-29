#include "packet.hpp"

Packet::Packet(u32 conn, std::vector<u8> data) : 
mconn(conn),
mdata(data)
{
}

std::vector<u8>& Packet::unpack()
{
    return mdata;
}

u32 Packet::conn()
{
    return mconn;
}