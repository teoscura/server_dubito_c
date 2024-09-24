#ifndef I_EPOLLHANDLER_H
#define I_EPOLLHANDLER_H

#include "../../defines/dint.hpp"
#include <sys/epoll.h>

using namespace dint;

class IEpollHandler
{   
    public:
        virtual void eventop(const u32 network_fd, const u8 op, const u32 state);
        virtual u32 wait(epoll_event *pevents, u32 maxevents, u32 timeout);
        virtual ~IEpollHandler() = default;
};

#endif