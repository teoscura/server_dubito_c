#include "network/networkserver.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    //TODO read from settings port number.
    std::cout<<"Cagasbusb1\n";
    NetworkServer server(25565);
    std::cout<<"Cagasbusb1.5\n";
    while(true)
    {
        std::cout<<"Cagasbusb2\n";
        auto t = server.p_incoming_packets();
        while(!t.empty())
        {
            server.send(t.front()->unpack(), t.front()->conn());
            t.erase(t.begin());
        }
    }
    std::cout<<"Cagasbusb3\n";
    server.close();
    return 0;
}