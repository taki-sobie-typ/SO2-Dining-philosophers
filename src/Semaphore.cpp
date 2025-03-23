// Created by Patryk on 20.03.2025.
// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the implementation of the Semaphore class.

#include "Semaphore.h"

Semaphore::Semaphore(int count) : count(count) {}

void Semaphore::wait() {
    std::unique_lock lock(mtx);  // Lock the mutex
    // Wait until count is greater than zero
    cv.wait(lock, [this] { return count > 0; });
    --count;  // Decrease the available resource count
}

bool Semaphore::try_wait() {
    std::unique_lock lock(mtx);
    if (count > 0) {
        --count;
        return true;
    }
    return false;
}

void Semaphore::signal() {
    std::unique_lock lock(mtx);  // Lock the mutex
    ++count;  // Increase the available resource count
    cv.notify_one();  // Notify one waiting thread
}
