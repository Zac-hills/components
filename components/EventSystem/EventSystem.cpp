#include "EventSystem.h"

EventInterface::~EventInterface() {}

EventSystem::EventSystem(unsigned int numOfThreads)
{
    unsigned int numThreads = numOfThreads;
    if (numOfThreads > std::thread::hardware_concurrency())
    {
        numThreads = std::thread::hardware_concurrency();
    }
    for (unsigned int i = 0; i < numOfThreads; ++i)
    {
        threads.push_back(std::thread());
    }
}

EventSystem::~EventSystem()
{
}

void EventSystem::add(EventInterface* e)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(e);
    conditionVariable.notify_one();
}

EventInterface* EventSystem::get()
{
    EventInterface* e;
    {
        std::lock_guard<std::mutex> lock(mutex);
        e = queue.front();
        queue.pop();
    }
    return e;
}
