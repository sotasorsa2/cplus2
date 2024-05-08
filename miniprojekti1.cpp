#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

// Abstract class for tasks
class Game_Task {
public:
    virtual void perform() = 0;
    virtual ~Game_Task() {}
};

class TaskQueue {
public:
    TaskQueue(int nof_threads) : num_threads(nof_threads), stop_flag(false) {
        // Create worker threads
        for (int i = 0; i < num_threads; ++i) {
            workers.emplace_back(std::bind(&TaskQueue::workerThread, this));
        }
    }

    // Add a job to the task queue
    void addJob(Game_Task* task) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            task_queue.push(task);
        }
        // Notify one worker thread
        cv.notify_one();
    }

    ~TaskQueue() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop_flag = true;
        }
        // Notify all worker threads to stop
        cv.notify_all();

        // Join worker threads
        for (std::thread& worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }

private:
    // Worker thread function
    void workerThread() {
        while (true) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // Wait until there's work to do or stop is requested
            cv.wait(lock, [this]() { return !task_queue.empty() || stop_flag; });

            // Check if stop is requested
            if (stop_flag && task_queue.empty()) {
                return;
            }

            // Get the next job from the queue
            Game_Task* task = task_queue.front();
            task_queue.pop();

            lock.unlock(); // Release the lock while performing the task
            // Perform the job
            task->perform();
            delete task; // Remember to delete the task object after performing it
        }
    }

    int num_threads; // Number of worker threads
    std::vector<std::thread> workers; // Worker threads
    std::queue<Game_Task*> task_queue; // Task queue
    std::mutex queue_mutex; // Mutex to protect access to the task queue
    std::condition_variable cv; // Condition variable for signaling
    bool stop_flag; // Flag to indicate if the task queue is being destroyed
};
