#include "util/bitstream/bitstream.hpp"
#include "defines/dint.hpp"
#include <iomanip>
#include <ios>
#include <iostream>

int main()
{
    BitStream bs;
    u8 a1 = 10;
    u16 a2 = 12;
    u32 a3 = 13131;
    bs << a1;
    bs << a2; 
    bs << a3;
    auto t = bs.read();
    std::cout << std::hex << std::setfill('0');
    for( u8 b : t) std::cout << std::setw(2) << int(b) << ' ';
    std::cout << '\n' ;
    return 0;
}