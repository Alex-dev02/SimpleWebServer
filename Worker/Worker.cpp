#include <iostream>

#include "Worker.hpp"

Worker::Worker(
        std::shared_ptr<std::queue<std::unique_ptr<NetworkStream>>> streamQueue,
        std::shared_ptr<std::atomic_uint32_t> queuedStreams,
        std::shared_ptr<std::mutex> mtx,
        std::shared_ptr<std::condition_variable> cond
    )
    : m_streamQueue(streamQueue),
    m_queuedStreams(queuedStreams),
    m_mtx(mtx),
    m_cond(cond)
    {
    }

void Worker::ProcessQueue() {
    std::unique_ptr<NetworkStream> currentStream;

    while (true) {
        std::unique_lock<std::mutex> locker((*m_mtx));
        m_cond->wait(locker, m_condPredicate);
        locker.unlock();

        while ((*m_queuedStreams) > 0) {
            locker.lock();
            currentStream = std::move(m_streamQueue->front());
            m_streamQueue->pop();
            locker.unlock();

            /*
            Process here the current request
            e.g.: interpret the http request and pass it to the router
            */
            //
            currentStream->Read(2048);
            currentStream->Write("Hello World!");
            currentStream->Close();
            //

            (*m_queuedStreams)--;
        }
    }
}
