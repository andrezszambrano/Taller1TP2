#ifndef TP2FINAL_THREADSAFEQUEUE_H
#define TP2FINAL_THREADSAFEQUEUE_H

#include "ManejaParticiones.h"
#include <queue>

class ThreadSafeQueue {
    std::queue<InfoParticion> cola;

public:
    ThreadSafeQueue();
    void push(InfoParticion&& info);
    void pop(InfoParticion& info);
    ~ThreadSafeQueue();
};

#endif //TP2FINAL_THREADSAFEQUEUE_H
