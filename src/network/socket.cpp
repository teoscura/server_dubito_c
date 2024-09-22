#include "socket.hpp"
#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

TCPSocket::TCPSocket(u32 port)
{
    mlistenconn.sock.sin_family = AF_INET;
    mlistenconn.sock.sin_addr.s_addr = INADDR_ANY;
    mlistenconn.sock.sin_port = htons(port);
    if((mlistenconn.sockfd = socket(AF_INET, SOCK_STREAM, 0)==-1)){
        //Failed to create socket
        exit(1);
    }
    if(bind(mlistenconn.sockfd, (sockaddr*)&mlistenconn.sock, mlistenconn.socksize)==-1){
        //Failed to bind to port
        exit(1);
    }
}

void TCPSocket::write(const Connection reciever, const std::vector<u8>& data) const
{
    if(send(reciever.sockfd, data.data(), data.size(), 0)==-1){
        //Failed to send data
        exit(1);
    }
}

std::vector<u8> TCPSocket::read(const u32 network_fd)
{
    u8 buf[0x1000] = {0};
    u32 nread = 0;
    std::vector<u8> read_bytes;
    while((nread=::read(mlistenconn.sockfd, buf, 0x1000))>0){
        read_bytes.insert(read_bytes.end(), buf, buf+nread);
        ::bzero(buf, sizeof(buf));
    }
    return read_bytes;
}

void TCPSocket::close()
{
    ::close(mlistenconn.sockfd);
    ::bzero(&mlistenconn.sock, sizeof(mlistenconn.sock));
}