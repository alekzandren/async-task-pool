#include "TaskQueue.hpp"

ThreadPool::ThreadPool(size_t threadCount) {
    m_workers.reserve(threadCount);
    for (size_t i = 0; i < threadCount; ++i) {
        m_workers.emplace_back([this, i](std::stop_token st) {
            workerLoop(st, i);
        });
    }
}

ThreadPool::~ThreadPool() {
    for (auto& worker : m_workers) {
        worker.request_stop();
    }
    m_cv.notify_all();
}

void ThreadPool::enqueue(Task task) {
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_tasks.push(std::move(task));
    }
    m_cv.notify_one();
}

void ThreadPool::workerLoop(std::stop_token stopToken, size_t id) {
    while (!stopToken.stop_requested()) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);

            m_cv.wait(lock, stopToken, [this]() {
                return !m_tasks.empty();
            });

            if (stopToken.stop_requested() && m_tasks.empty()) {
                return;
            }

            if (!m_tasks.empty()) {
                task = std::move(m_tasks.front());
                m_tasks.pop();
            }
        }

        if (task) {
            task();
        }
    }
}