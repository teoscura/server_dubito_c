#include "network/networkserver.hpp"

int main(int argc, char** argv)
{
    NetworkServer server(25565);
    server.close();
    return 0;
}