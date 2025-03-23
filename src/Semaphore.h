// Created by Patryk on 20.03.2025.
// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the declaration of the Semaphore class.

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#pragma once
#include <mutex>
#include <condition_variable>

class Semaphore {
 private:
    std::mutex mtx;  // Mutex for synchronization
    std::condition_variable cv;  // Condition variable for blocking threads
    int count;  // The count of available resources

 public:
    // Constructor initializes the semaphore count
    explicit Semaphore(int count = 1);

    // Copy Blocking
    Semaphore(const Semaphore&) = delete;  // Prevent copying
    Semaphore& operator=(const Semaphore&) = delete;  // Prevent assignment

    // Decrements the semaphore count, blocking if necessary
    bool try_wait();

    // Decrements the semaphore count, blocking if necessary
    void wait();

    // Increments the semaphore count, waking up a waiting thread if any
    void signal();
};

#endif  // SEMAPHORE_H
