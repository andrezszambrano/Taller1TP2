#ifndef TP2FINAL_THREADSAFEQUEUE_H
#define TP2FINAL_THREADSAFEQUEUE_H

#include "ManejaParticiones.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue {
    std::queue<InfoParticion> cola;
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    ThreadSafeQueue();
    void push(InfoParticion&& info);
    void pop(InfoParticion& info);
    //int size();
    ~ThreadSafeQueue();
};

#endif //TP2FINAL_THREADSAFEQUEUE_H
