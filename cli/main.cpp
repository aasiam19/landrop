#include <iostream>

#include "net.hpp"

int main() {
    try {
        landrop::Socket server = landrop::Socket::listenOn(45455);
        std::cout << "Listening on port 45455 ...\n";

        std::string ip;
        landrop::Socket client = server.accept(&ip);
        std::cout << "Connected from " << ip << "\n";

        char buf[1024];
        while (true) {
            size_t n = client.recvSome(buf, sizeof buf);
            if (n == 0) break;              // other side closed
            std::cout.write(buf, static_cast<std::streamsize>(n));
            std::cout.flush();
        }
        std::cout << "Peer disconnected.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
