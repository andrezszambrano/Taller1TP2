#include "ThreadSafeQueue.h"
#include "ManejaParticiones.h"
#include <utility>

ThreadSafeQueue::ThreadSafeQueue() {
}

void ThreadSafeQueue::push(InfoParticion&& info) {
    this->cola.push(std::move(info));
}

void ThreadSafeQueue::pop(InfoParticion& info) {
    info = this->cola.front();
    this->cola.pop();
}

ThreadSafeQueue::~ThreadSafeQueue() {
}

