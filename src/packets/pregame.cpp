#include "pregame.hpp"

PConnectToRoom::PConnectToRoom(Connection recipient, std::string username) :
DsPacket(recipient),
mlen(username.length()),
mplayername(username)
{
}