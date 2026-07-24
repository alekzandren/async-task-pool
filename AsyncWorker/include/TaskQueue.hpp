#ifndef TASK_QUEUE_HPP
#define TASK_QUEUE_HPP

#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <stop_token>
#include <iostream>

using Task = std::function<void()>;

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    void enqueue(Task task);

private:
    std::queue<Task> m_tasks;
    std::mutex m_queueMutex;
    std::condition_variable_any m_cv;
    std::vector<std::jthread> m_workers;
    
    void workerLoop(std::stop_token stopToken, size_t id);
};

#endif // TASK_QUEUE_HPP