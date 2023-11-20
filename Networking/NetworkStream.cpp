#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "NetworkStream.hpp"

NetworkStream::NetworkStream(int sock_fd)
    : m_sock_fd(sock_fd)
    {}

const std::string NetworkStream::Read(unsigned int bufferSize) {
    char buff[bufferSize];
    int bytes = recv(m_sock_fd, buff, bufferSize, 0);
    if (bytes == -1) {
        std::cerr << "Failed to recv()\n";
        return std::string();
    }
    buff[bytes] = '\0';
    return buff;
}

void NetworkStream::Write(const std::string& data) {
    int err = send(m_sock_fd, data.c_str(), data.length(), 0);
    if (err == -1)
        std::cerr << "Failed to write: " + *strerror(err) << "\n";
}

void NetworkStream::Close() {
    close(m_sock_fd);
}
