#include "../defines/dint.hpp"

#include <netinet/in.h>
#include <sys/epoll.h>

using namespace dint;

struct Connection{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

class ISocket
{
    public:
        virtual void bind(Connection socket);
        virtual void write(u32 network_fd);
        virtual void read(u32 network_fd);
        virtual void close();
};

class IEpollHandler
{   
    public:
        virtual void eventop(u32 network_fd, u8 op);
        virtual void 
};