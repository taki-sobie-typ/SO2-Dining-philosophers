// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the implementation of the Dining Philosophers problem.

#include <iostream>
#include <thread>
#include <vector>
#include <memory>  // For smart pointers
#include "Semaphore.h"
#include "Philosopher.h"

// Platform-specific command to clear the console screen
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"  // Windows command
#else
    #define CLEAR_SCREEN "clear"  // Linux/Unix command
#endif

constexpr int NUM_PHILOSOPHERS = 10;  // Number of philosophers
constexpr int MAX_HUNGER = 10;  // Maximum hunger level a philosopher can have

bool areAnyPhilosophersAlive(const std::vector<Philosopher> &philosophers) {
    for (const auto& philosopher : philosophers) {
        if (philosopher.get_isAlive()) {
            return true;  // At least one philosopher is still alive
        }
    }
    return false;  // All philosophers are dead
}


// Function to display the status of all philosophers periodically
void displayStatus(const std::vector<Philosopher> &philosophers) {
    while (areAnyPhilosophersAlive(philosophers)) {
        system(CLEAR_SCREEN);  // Clear the console screen before displaying new status
        std::cout << "ID\tHUNGER\tSTATUS\t" << std::endl;

        // Iterate through each philosopher and display their status
        for (const auto& philosopher : philosophers) {
            std::cout << philosopher.get_id() << "\t"
                      << philosopher.get_hunger() << "\t"
                      << philosopher.get_state() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Update status every second
    }
}

int main() {
    // Create semaphores representing forks (one for each philosopher)
    std::vector<std::unique_ptr<Semaphore>> forks;
    forks.reserve(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        forks.push_back(std::make_unique<Semaphore>(1));  // Each fork starts as available (value = 1)
    }

    // Create philosophers and assign them to forks
    std::vector<Philosopher> philosophers;
    philosophers.reserve(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(
            i,  // Philosopher ID
            *forks[i],  // Left fork (same index)
            *forks[(i + 1) % NUM_PHILOSOPHERS],  // Right fork (next index, wraps around)
            MAX_HUNGER);  // Initial hunger level
    }

    // Create threads for each philosopher
    std::vector<std::thread> philosophersThreads;
    philosophersThreads.reserve(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophersThreads.emplace_back(
            &Philosopher::operator(),  // Start philosopher's behavior loop
            &philosophers[i]);  // Pass the philosopher object
    }

    // Start a separate thread to display the status of all philosophers
    std::thread displayThread(displayStatus, std::ref(philosophers));
    displayThread.detach();  // Detach it so it runs independently

    // Wait for all philosopher threads to finish (which won't happen in an infinite simulation)
    for (auto& philosopher : philosophersThreads) {
        philosopher.join();
    }

    return 0;  // Program should never reach this point since philosophers run indefinitely
}
