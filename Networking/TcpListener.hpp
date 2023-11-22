#pragma once

#include <cstdint>
#include <memory>

#include "NetworkStream.hpp"

class TcpListener {

public:
    TcpListener(std::uint16_t port, std::uint16_t backlog);

    void Start();
    void Stop();
    
    [[nodiscard]]
    std::unique_ptr<NetworkStream> AcceptClient();

private:
    std::uint16_t m_port;
    std::uint16_t m_backlog;
    int m_sock_fd;

    void Init();
    void SetupSocketSpecs(struct addrinfo& hints);
    void BindToSocket(struct addrinfo* p, struct addrinfo* servinfo, int& yes);
    void *get_in_addr(struct sockaddr *sa);
};
