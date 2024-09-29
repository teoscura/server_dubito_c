#ifndef EPOLLHANDLER_H
#define EPOLLHANDLER_H

#include "../api/network/iepollhandler.hpp"

class EpollHandler : public IEpollHandler
{
    private:
        u32 mepollfd;
    public:
        EpollHandler(u32 listenerfd);
        void eventop(const u32 network_fd, const u8 op, const u32 state) override;
        u32 wait(epoll_event *pevents, u32 maxevents, u32 timeout) override;
        ~EpollHandler();
};


#endif