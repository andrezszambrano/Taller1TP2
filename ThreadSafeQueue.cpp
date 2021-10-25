#include "ThreadSafeQueue.h"
#include "ManejaParticiones.h"
#include <utility>

ThreadSafeQueue::ThreadSafeQueue() {
}

void ThreadSafeQueue::push(InfoParticion&& info) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->cola.push(std::move(info));
    this->condition_variable.notify_all();
}

void ThreadSafeQueue::pop(InfoParticion& info) {
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->cola.empty())
        this->condition_variable.wait(uniqueLock);
    info = this->cola.front();
    this->cola.pop();
}

/*
int ThreadSafeQueue::size() {
    return this->cola.size();
}*/

ThreadSafeQueue::~ThreadSafeQueue() {
}

