#pragma once
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>

namespace landrop {

// Wraps one network socket. When the object goes away, the socket closes itself.
class Socket {
public:
    Socket() = default;
    explicit Socket(int fd) : fd_(fd) {}
    ~Socket() { close(); }

    // A socket can be moved but not copied (two owners would close it twice).
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&& o) noexcept : fd_(std::exchange(o.fd_, -1)) {}
    Socket& operator=(Socket&& o) noexcept {
        if (this != &o) { close(); fd_ = std::exchange(o.fd_, -1); }
        return *this;
    }

    void close() {
        if (fd_ >= 0) { ::close(fd_); fd_ = -1; }
    }

    // Start listening for incoming connections on this port.
    static Socket listenOn(uint16_t port) {
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0) throw std::runtime_error(err("socket"));
        Socket s(fd);

        int yes = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (::bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof addr) != 0)
            throw std::runtime_error(err("bind"));
        if (::listen(fd, 8) != 0) throw std::runtime_error(err("listen"));
        return s;
    }

    // Wait until someone connects. Returns the new connection.
    Socket accept(std::string* peerIp = nullptr) {
        sockaddr_in addr{};
        socklen_t len = sizeof addr;
        int c = ::accept(fd_, reinterpret_cast<sockaddr*>(&addr), &len);
        if (c < 0) throw std::runtime_error(err("accept"));
        if (peerIp) {
            char ip[INET_ADDRSTRLEN] = {};
            inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof ip);
            *peerIp = ip;
        }
        return Socket(c);
    }

    // Read up to n bytes. Returns how many arrived; 0 means the other side closed.
    size_t recvSome(void* buf, size_t n) {
        while (true) {
            ssize_t r = ::recv(fd_, buf, n, 0);
            if (r >= 0) return static_cast<size_t>(r);
            if (errno != EINTR) throw std::runtime_error(err("recv"));
        }
    }

private:
    static std::string err(const std::string& what) {
        return what + ": " + std::strerror(errno);
    }
    int fd_ = -1;
};

} // namespace landrop
