#include "ThreadpoolManager.h"

namespace RCU {

void ThreadpoolManager::_ThreadLoop()
{
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(_QueueMutex);
            _MutexCondition.wait(lock, [this] {
                return !_Jobs.empty() || _ShouldTerminate;
            });
            if (_ShouldTerminate) {
                return;
            }
            job = _Jobs.front();
            _Jobs.pop();
        }
        job();
    }
}

void ThreadpoolManager::Start()
{
    // Max # of thrads available on hardware
    const uint32_t numThreads = std::thread::hardware_concurrency();
    _Threads.resize(numThreads);
    for (uint32_t i = 0; i < numThreads; i++) {
        _Threads.at(i) = std::thread(&RCU::ThreadpoolManager::_ThreadLoop,this);
    }
}

void ThreadpoolManager::QueueJob(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> lock(_QueueMutex);
        _Jobs.push(job);
    }
    _MutexCondition.notify_one();
}

void ThreadpoolManager::Stop()
{
    {
        std::unique_lock<std::mutex> lock(_QueueMutex);
        _ShouldTerminate = true;
    }
    _MutexCondition.notify_all();
    for(std::thread & activeThread : _Threads) {
        activeThread.join();
    }
    _Threads.clear();
}

bool ThreadpoolManager::Busy()
{
    bool poolBusy;
    {
        std::unique_lock<std::mutex> lock(_QueueMutex);
        poolBusy = !_Jobs.empty();
    }
    return poolBusy;
}

}