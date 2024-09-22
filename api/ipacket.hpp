#include "../defines/dint.hpp"

#include <vector>

using namespace dint;

class IPacket 
{
    public:
        virtual std::vector<std::byte> read();
        virtual ~IPacket() = default;
};

class IDsPacket
{
    public:
        virtual IPacket serialize();
        virtual ~IDsPacket() = default;
};