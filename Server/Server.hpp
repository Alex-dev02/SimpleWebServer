#pragma once

#include <memory>
#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <string>

#include <Networking/TcpListener.hpp>
#include <Networking/NetworkStream.hpp>

class Server {

public:
    Server(
        std::unique_ptr<TcpListener> listener,
        std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> streamQueue,
        std::shared_ptr<std::atomic_uint32_t> queuedStreams,
        std::shared_ptr<std::mutex> mtx,
        std::shared_ptr<std::condition_variable> cond
    );
    Server(const Server&) = delete;
    Server& operator= (const Server&) = delete;

    void Listen();

private:
    std::unique_ptr<TcpListener> m_listener;
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> m_streamQueue;
    std::shared_ptr<std::atomic_uint32_t> m_queuedStreams;
    std::shared_ptr<std::mutex> m_mtx;
    std::shared_ptr<std::condition_variable> m_cond;
};
