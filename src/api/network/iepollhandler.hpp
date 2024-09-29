#ifndef I_EPOLLHANDLER_H
#define I_EPOLLHANDLER_H

#include "../../defines/dint.hpp"
#include <sys/epoll.h>

using namespace dint;

class IEpollHandler
{   
    public:
        virtual void eventop(const u32 network_fd, const u8 op, const u32 state) = 0;
        virtual u32 wait(epoll_event *pevents, u32 maxevents, u32 timeout) = 0;
        virtual ~IEpollHandler() = 0;
};

#endif