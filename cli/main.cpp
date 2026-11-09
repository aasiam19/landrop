#include <iostream>
#include <unistd.h>

int main() {
    char host[256] = {};
    gethostname(host, sizeof host - 1);

    std::cout << "LanDrop is alive on host: " << host << "\n";
    return 0;
}
