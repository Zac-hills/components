#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <iostream>
#include <tuple>
#include <utility>
class EventInterface
{
public:
    virtual ~EventInterface() = 0;
    virtual void call() = 0;
private:
};

template <typename... args>
class Event : public EventInterface
{
public:
    Event(std::function<void(args...)>func, args... arggs)
    {
        callback = func;
        params = std::make_tuple(arggs...);
    }
    ~Event() {}
    void call() { execute(); };

private:
    void execute()
    {
        std::apply(callback, params);
    };
    std::tuple<args...> params;
    std::function<void(args...)> callback;
};

class EventSystem
{
public:
    EventSystem(unsigned int numOfThreads);
    ~EventSystem();
    void add(EventInterface *);
    EventInterface* get();

private:
    std::vector<std::thread> threads;
    std::queue<EventInterface *> queue;
    std::mutex mutex;
    std::condition_variable conditionVariable;
};

class Worker
{
public:
    Worker(std::condition_variable& conditionVariable, EventSystem& taskManager);

    ~Worker();
    //loop
    void loop();
    //wait until notified
    void wait();
    //execute
    void execute();
private:
    std::thread thread;
    std::condition_variable& conditionVariable;
    EventSystem& taskManager;
    std::mutex mutex;
    bool running = true;
    static unsigned int counter;
    unsigned int id;
};