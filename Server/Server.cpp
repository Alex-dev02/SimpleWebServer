#include <iostream>
#include <thread>

#include "Server.hpp"

Server::Server(
    std::unique_ptr<TcpListener> listener,
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> streamQueue,
    std::shared_ptr<std::atomic_uint32_t> queuedStreams,
    std::shared_ptr<std::mutex> mtx,
    std::shared_ptr<std::condition_variable> cond
)
    : m_listener(std::move(listener)),
    m_streamQueue(streamQueue),
    m_queuedStreams(queuedStreams),
    m_mtx(mtx),
    m_cond(cond)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

void Server::Listen() {
    m_listener->Start();
    
    std::cout << "Server successfully started listening\n";

    while (true) {
        std::unique_ptr<NetworkStream> stream = m_listener->AcceptClient();
        m_mtx->lock();
        (*m_queuedStreams)++;
        m_streamQueue->push(std::move(stream));
        std::cout << "New requested added to queue\n";
        if ((*m_queuedStreams) == 1)
            m_cond->notify_one();
        m_mtx->unlock();
    }
}