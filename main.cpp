#include <iostream>
#include <memory>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <Networking/NetworkStream.hpp>
#include <Networking/TcpListener.hpp>
#include <Server/Server.hpp>

int main() {
    std::uint16_t port = 5000;
    std::uint16_t backlog = 10;

    std::unique_ptr<TcpListener> listener = std::make_unique<TcpListener>(port, backlog);
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> queue = std::make_shared<std::queue<std::unique_ptr<NetworkStream>>>();
    std::shared_ptr<std::atomic_uint32_t> queuedStreams = std::make_shared<std::atomic_uint32_t>();
    std::shared_ptr<std::mutex> mtx = std::make_shared<std::mutex>();
    std::shared_ptr<std::condition_variable> cond = std::make_shared<std::condition_variable>();

    Server s(std::move(listener), queue, queuedStreams, mtx, cond);

    s.Listen();

    return 0;
}
