#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include "../api/network/inetworkserver.hpp"
#include "epollhandler.hpp"
#include "tcpsocket.hpp"

class NetworkServer : public INetworkServer, public TCPSocket, public EpollHandler
{
    private:
        std::vector<Connection> mconnusers;
        bool mconnected(Connection conn);
        void mnewconn(epoll_event ev);
    public:
        NetworkServer(u32 port);
        std::vector<IPacket*> p_incoming_packets() override; 
        void send(std::vector<u8> data, u32 recipient) override;
        ~NetworkServer();
};

#endif