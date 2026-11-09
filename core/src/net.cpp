#include "landrop/net.hpp"

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
#else
  #include <unistd.h>
  #include <limits.h>
#endif

namespace landrop {

void netInit() {
#ifdef _WIN32
    static const bool once = [] {
        WSADATA data;
        return WSAStartup(MAKEWORD(2, 2), &data) == 0;
    }();
    (void)once;
#endif
}

std::string hostName() {
    char buf[256] = {};
    if (gethostname(buf, sizeof buf - 1) != 0) return "unknown";
    return buf;
}

std::string platformName() {
#ifdef _WIN32
    return "Windows";
#elif defined(__linux__)
    return "Linux";
#else
    return "Other";
#endif
}

} // namespace landrop
