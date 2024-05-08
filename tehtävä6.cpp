#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <algorithm>

class Game_Task {
public:
    virtual void perform() = 0;
    virtual ~Game_Task() {} // Virtual destructor for polymorphic behavior
};

// Example subclass
class Example_Task : public Game_Task {
public:
    void perform() override {
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Example_Task performed." << std::endl;
    }
};

int main() {
    std::vector<Game_Task*> tasks;

    // Populate tasks vector with example tasks
    for (int i = 0; i < 10; ++i) {
        tasks.push_back(new Example_Task());
    }

    auto start_time = std::chrono::steady_clock::now();

    // Launch asynchronous tasks to perform tasks in parallel
    std::vector<std::future<void>> futures;
    for (int i = 0; i < tasks.size(); ++i) {
        futures.emplace_back(std::async(std::launch::async, &Game_Task::perform, tasks[i]));
    }

    // Wait for all tasks to complete
    for (auto& fut : futures) {
        fut.wait();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Parallel execution time: " << duration << " milliseconds" << std::endl;

    // Clean up
    for (Game_Task* task : tasks) {
        delete task;
    }

    return 0;
}
