#include "packet.hpp"

Packet::Packet(std::vector<u8> data) : mdata(data)
{
}

std::vector<u8>& Packet::unpack(){
    return mdata;
}