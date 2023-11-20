#pragma once

#include <cstdint>

class TcpListener {

public:
    TcpListener(std::uint16_t port, std::uint16_t backlog);

private:
    std::uint16_t m_port;
    std::uint16_t m_backlog;
};
