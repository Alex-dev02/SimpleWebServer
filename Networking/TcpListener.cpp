#include "TcpListener.hpp"

TcpListener::TcpListener(std::uint16_t port, std::uint16_t backlog)
    : m_port(port),
    m_backlog(backlog)

{}
