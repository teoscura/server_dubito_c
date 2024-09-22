#ifndef I_SOCKET_H
#define I_SOCKET_H

#include "../../defines/dint.hpp"

#include <netinet/in.h>
#include <vector>

using namespace dint;

struct Connection
{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

class ITCPSocket
{
    public:
        virtual void write(const Connection reciever, const std::vector<u8>& data) const;
        virtual std::vector<u8> read(const u32 network_fd);
        virtual void close();
        virtual ~ITCPSocket() = default;
};

#endif