#include "../../defines/params.hpp"
#include "networkserver.hpp"
#include "epollhandler.hpp"
#include "tcpsocket.hpp"
#include "packet.hpp"
#include <cstdlib>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>


NetworkServer::NetworkServer(u32 port) :
TCPSocket(port),
EpollHandler(TCPSocket::connection().sockfd)
{}

void NetworkServer::newconn(epoll_event ev)
{
    Connection newconn;
    if((newconn.sockfd = accept(TCPSocket::connection().sockfd, (sockaddr*) &newconn.sock, &newconn.socksize))==-1)
    {
        //Accept Error
        exit(1);
    }
    EpollHandler::eventop(newconn.sockfd, EPOLL_CTL_ADD, EPOLLIN);
    mconnusers.push_back(newconn);
}

std::vector<IPacket> NetworkServer::incoming_packets()
{
    epoll_event pevents[MAXCONNS];
    std::vector<IPacket> res;
    wait(pevents, MAXCONNS, ETIMEOUT);
    for(epoll_event t : pevents)
    {
        if(t.data.fd == TCPSocket::connection().sockfd)
        {
            for(Connection c : mconnusers)
            {
                if(c.sockfd == t.data.fd)
                {
                    //TODO send connection already present message!
                    continue;
                }
            }
            newconn(t);
            continue;
        }
        if(t.events & EPOLLIN)
        {
            
            Packet p = Packet(t.data.fd, TCPSocket::read(t.data.fd));
            if(p.unpack().size()==0)
            {
                EpollHandler::eventop(p.conn(), EPOLL_CTL_DEL, EPOLLIN);
                continue;
            }
            res.push_back(p);
            continue;
        }
        else{
            continue;
        }
    }
    return res;
}

void NetworkServer::send(std::vector<u8> data, u32 recipient)
{
    for(Connection t : mconnusers)
    {
        if(t.sockfd == recipient)
        {
            TCPSocket::write(t, data);
            return;
        }
    }
    //No user present error TODO
    return;
}

NetworkServer::~NetworkServer()
{
    for(Connection t : mconnusers)
    {
        ::close(t.sockfd);
    }
    TCPSocket::close();
}