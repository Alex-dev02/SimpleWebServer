#pragma once

#include <string>

class NetworkStream {

public:
    NetworkStream(int sock_fd);

    [[nodiscard]]
    const std::string Read(unsigned int bufferSize);
    void Write(const std::string& data);
    void Close();

private:
    int m_sock_fd;
};
