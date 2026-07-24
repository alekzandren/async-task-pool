#include "TaskQueue.hpp"
#include <chrono>
#include <syncstream>

void processSampleTask(int taskId) {
    std::osyncstream(std::cout) << "[Task " << taskId
                                << "] Started on thread: "
                                << std::this_thread::get_id() << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(100 + (taskId % 3) * 50));

    std::osyncstream(std::cout) << "[Task " << taskId << "] Completed.\n";
}

int main() {
    std::cout << "Starting ThreadPool (C++23) in CLion...\n";

    {
        ThreadPool pool(4);

        for (int i = 1; i <= 10; ++i) {
            pool.enqueue([i]() {
                processSampleTask(i);
            });
        }

        std::cout << "All tasks queued. Waiting for execution...\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "All tasks processed. Program finished successfully.\n";
    return 0;
}