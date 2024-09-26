#ifndef SOCKET_H
#define SOCKET_H

#include "../../api/network/itcpsocket.hpp"

class TCPSocket : public ITCPSocket 
{
    private:
        Connection mlistenconn;
    public:
        TCPSocket(u32 port);
        Connection connection() const;
        void write(const Connection reciever, const std::vector<u8>& data) const override;
        std::vector<u8> read(const u32 network_fd) override;
        void close() override; 
};

#endif