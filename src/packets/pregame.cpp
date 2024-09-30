#include "pregame.hpp"
#include "dspacket.hpp"
#include "packet.hpp"
#include <memory>

PConnectToRoom::PConnectToRoom(Connection recipient, std::string username) :
DsPacket(recipient),
mlen(username.length()),
mplayername(username)
{
}

std::shared_ptr<IPacket> const PConnectToRoom::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x01);
    //Username lenght
    bytes.push_back(mlen);
    for(char t: mplayername)
    {
        bytes.push_back(t);
    }
    return std::make_shared<Packet>(mrecipient.sockfd, bytes);
}

PAccept::PAccept(Connection recipient, u8 pid, u8 key) :
DsPacket(recipient),
mpid(pid),
mkey(key)
{
}

std::shared_ptr<IPacket> const PAccept::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x02);
    //Pid
    bytes.push_back(mpid);
    //Key
    bytes.push_back(mkey);
    return std::make_shared<Packet>(mrecipient.sockfd, bytes); 
}

PRoomPing::PRoomPing(Connection recipient, u32 tick) :
DsPacket(recipient),
mtick(tick)
{
}

std::shared_ptr<IPacket> const PRoomPing::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x03);
    //Tick
    for(u8 i = 3; i > 0; i--)
    {
        bytes.push_back(mtick<<(8*i));
    }
    return std::make_shared<Packet>(mrecipient.sockfd, bytes);
}

PReadyCheck::PReadyCheck(Connection recipient, u8 pid, u8 key, bool ready) :
DsPacket(recipient),
mpid(pid),
mkey(key),
mready(ready)
{
}

std::shared_ptr<IPacket> const PReadyCheck::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x04);
    //Player ID
    bytes.push_back(mpid);
    //Key
    bytes.push_back(mkey);
    //Bool
    bytes.push_back(mready);
    return std::make_shared<Packet>(mrecipient.sockfd, bytes);
}

PCountdownStart::PCountdownStart(Connection recipient, u8 seconds) :
DsPacket(recipient),
mseconds(seconds)
{
}

std::shared_ptr<IPacket> const PCountdownStart::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x05);
    //Seconds
    bytes.push_back(mseconds);
    return std::make_shared<Packet>(mrecipient.sockfd, bytes);
}

PGameStart::PGameStart(Connection recipient, std::vector<u8> data, u8 pid) : 
DsPacket(recipient),
mdata(data),
mpid(pid)
{
}

std::shared_ptr<IPacket> const PGameStart::serialize()
{
    std::vector<u8> bytes;
    //ID
    bytes.push_back(0x06);
    //Data
    bytes.insert(bytes.end(), mdata.begin(), mdata.end());
    //PID
    bytes.push_back(mpid);
    return std::make_unique<Packet>(mrecipient.sockfd, bytes);
}