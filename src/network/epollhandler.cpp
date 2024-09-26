#include "epollhandler.hpp"
#include <cstdlib>
#include <sys/epoll.h>
#include <unistd.h>

EpollHandler::EpollHandler(u32 listenerfd)
{
    mepollfd = epoll_create(1);
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = listenerfd;
    if((epoll_ctl(mepollfd, EPOLL_CTL_ADD, listenerfd, &ev))==-1)
    {
        //Epoll Error
        exit(1);
    }
}

void EpollHandler::eventop(const u32 network_fd, const u8 op, const u32 state)
{
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = network_fd;
    switch(op)
    {
        case EPOLL_CTL_ADD:
            if (epoll_ctl(mepollfd, EPOLL_CTL_ADD, network_fd, &ev) < 0) 
            {
                //Epoll Add Error
                exit(1);
            }
            break;
        case EPOLL_CTL_DEL:
            if (epoll_ctl(mepollfd, EPOLL_CTL_DEL, network_fd, &ev) < 0) 
            {
                //Epoll Del Error
                exit(1);
            }
            ::close(ev.data.fd);
            break;
        case EPOLL_CTL_MOD:
            if (epoll_ctl(mepollfd, EPOLL_CTL_MOD, network_fd, &ev) < 0) 
            {
                //Epoll Mod Error
                exit(1);
            }   
            break;
        default:
            break;
    }
}

u32 EpollHandler::wait(epoll_event *pevents, u32 maxevents, u32 timeout)
{
    u32 nevents;
    if((nevents = epoll_wait(mepollfd, pevents, maxevents, timeout))<0)
    {
        //Epoll Wait Error
        exit(1);
    }
    return nevents;
}

EpollHandler::~EpollHandler()
{
    close(mepollfd);
}