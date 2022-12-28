#ifndef THREADPOOL_MANAGER_H
#define THREADPOOL_MANAGER_H

#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

namespace RCU {

class ThreadpoolManager {
private:
    void _ThreadLoop();

    // Tells the threadpool manager to stop looking for jobs
    bool _ShouldTerminate = false;
    // Prevents data races to the job queue
    std::mutex _QueueMutex;
    // Allows threads to wait on new jobs or termination
    std::condition_variable _MutexCondition;
    std::vector<std::thread> _Threads;
    std::queue<std::function<void()>> _Jobs;

public: 
    void Start();
    void QueueJob(const std::function<void()>& job);
    void Stop();
    bool Busy();
};

};
#endif // THREADPOOL_MANAGER_H