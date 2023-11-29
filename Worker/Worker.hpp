#pragma once

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <functional>

#include <Networking/NetworkStream.hpp>

class Worker {

public:
    Worker(
        std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> streamQueue,
        std::shared_ptr<std::atomic_uint32_t> queuedStreams,
        std::shared_ptr<std::mutex> mtx,
        std::shared_ptr<std::condition_variable> cond
    );

    void ProcessQueue();

private:
    std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> m_streamQueue;
    std::shared_ptr<std::atomic_uint32_t> m_queuedStreams;
    std::shared_ptr<std::mutex> m_mtx;
    std::shared_ptr<std::condition_variable> m_cond;
    std::function<bool()> m_condPredicate =
        [this]() {
            return (*m_queuedStreams) != 0;
        };
};