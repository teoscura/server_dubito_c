#include "networkserver.hpp"

#include "../defines/params.hpp"
#include "../packets/packet.hpp"
#include "epollhandler.hpp"
#include "tcpsocket.hpp"

#include <cstdlib>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>


NetworkServer::NetworkServer(u32 port) :
TCPSocket(port),
EpollHandler(TCPSocket::connection().sockfd)
{}

void NetworkServer::mnewconn(epoll_event ev)
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

std::vector<IPacket*> NetworkServer::p_incoming_packets()
{
    epoll_event pevents[MAXCONNS];
    std::vector<IPacket*> pres;
    EpollHandler::wait(pevents, MAXCONNS, ETIMEOUT);
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
            mnewconn(t);
            continue;
        }
        if(t.events & EPOLLIN)
        {
            Packet *p = new Packet(t.data.fd, TCPSocket::read(t.data.fd));
            if(p->unpack().size()==0)
            {
                EpollHandler::eventop(p->conn(), EPOLL_CTL_DEL, EPOLLIN);
                continue;
            }
            pres.push_back(p);
            continue;
        }
        else{
            continue;
        }
    }
    return pres;
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