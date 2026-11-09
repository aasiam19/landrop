#include <iostream>
#include "landrop/net.hpp"

int main() {
    landrop::netInit();
    std::cout << "LanDrop skeleton OK\n"
              << "  platform: " << landrop::platformName() << "\n"
              << "  host:     " << landrop::hostName() << "\n";
    return 0;
}
