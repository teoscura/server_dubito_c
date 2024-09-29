#ifndef P_WAITINGROOM_H
#define P_WAITINGROOM_H

#include "dspacket.hpp"
#include <string>

/* - Connect to Room packet - 0x01 - - 
    c->s: sent at the very start, ID - Username Lenght - Username.
    s->c: is sent back ico error, ID - Reason Lenght - Reason. 
 - - - - - - - - - - - - - - - - - - - */
class PConnectToRoom : public DsPacket
{
    private:
        u8 mlen;
        std::string mplayername;
    public:
        PConnectToRoom(Connection recipient, std::string reason);
        std::string& gusername() { return mplayername; }; 
        IPacket const serialize() override;
        ~PConnectToRoom() override = default;
};

/* - Accept packet - 0x02  - - - - - - 
    ONLY!
    s->c: sent in response to a correct connect, ID - Player Seat ID - Key.
 - - - - - - - - - - - - - - - - - - - */
class PAccept : public DsPacket 
{
    private: 
        u8 mpid;
        u8 mkey;
    public:
        PAccept(Connection recipient, u8 pid, u8 key);
        IPacket const serialize() override;
        ~PAccept() override = default;
};

/* - Ping Packet - 0x03  - - - - - - 
    c->s: response to server, ID - Current Tick.
    s->c: sent every 4 ticks, ID - Current Tick.
 - - - - - - - - - - - - - - - - - - - */
class PRoomPing : public DsPacket
{
    private:
        u32 mtick;
    public:
        PRoomPing(Connection recipient, u32 tick);
        u32 const gtick() {return mtick;};
        IPacket const serialize() override;
        ~PRoomPing() override = default;
};

/* - Ready Packet - 0x04  - - - - - - 
    c->s: sent to server, ID - PlayerID - Key - Bool.
    s->c: resp to client, ID - PlayerID - Key - Bool.
 - - - - - - - - - - - - - - - - - - - */
class PReadyCheck : public DsPacket
{
    private:
        u8 mpid;
        u8 mkey;
        bool mready;
    public:
        PReadyCheck(Connection recipient, u8 pid, u8 key, bool ready);
        u8 const gpid() { return mpid; };
        u8 const gkey() { return mkey; };
        bool const gready() { return mready; };
        IPacket const serialize() override;
        ~PReadyCheck() override = default;
};

/* - Countdown Start - 0x05  - - - - - - 
    ONLY!
    s->c: sent to start the coutndown, ID - Seconds.
 - - - - - - - - - - - - - - - - - - - */
class PCountdownStart : public DsPacket
{
    private:
        u8 mseconds;
    public:
        PCountdownStart(Connection recipient, u8 seconds);
        IPacket const serialize() override;
        ~PCountdownStart() override = default;
};

/* - Game Start - 0x08  - - - - - - 
    ONLY!
    s->c: sent to start the game, array of:
    Number of Players in a short,
    Length of Username - Username - ID  X Number of players,
    ID of player.
 - - - - - - - - - - - - - - - - - - - */
class PGameStart : public DsPacket
{
    private:
        std::vector<u8> mdata;
    public:
        PGameStart(Connection recipient, std::vector<u8> data);
        std::vector<u8>& gdata() { return mdata; };
        IPacket const serialize() override;
        ~PGameStart() override = default;
};

#endif