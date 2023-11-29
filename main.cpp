#include <iostream>
#include <memory>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>

#include <Networking/NetworkStream.hpp>
#include <Networking/TcpListener.hpp>
#include <Server/Server.hpp>
#include <Worker/Worker.hpp>

void LaunchServer(
    std::unique_ptr<TcpListener> listener,
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> queue,
    std::shared_ptr<std::atomic_uint32_t> queuedStreams, std::shared_ptr<std::mutex> mtx,
    std::shared_ptr<std::condition_variable> cond
) {

    Server s(std::move(listener), queue, queuedStreams, mtx, cond);
    s.Listen();

}

int main() {
    std::uint16_t port = 5000;
    std::uint16_t backlog = 10;

    std::unique_ptr<TcpListener> listener = std::make_unique<TcpListener>(port, backlog);
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> queue = std::make_shared<std::queue<std::unique_ptr<NetworkStream>>>();
    std::shared_ptr<std::atomic_uint32_t> queuedStreams = std::make_shared<std::atomic_uint32_t>();
    std::shared_ptr<std::mutex> mtx = std::make_shared<std::mutex>();
    std::shared_ptr<std::condition_variable> cond = std::make_shared<std::condition_variable>();

    std::thread server(LaunchServer, std::move(listener), queue, queuedStreams, mtx, cond);
    server.detach();

    Worker worker(queue, queuedStreams, mtx, cond);
    worker.ProcessQueue();

    return 0;
}
