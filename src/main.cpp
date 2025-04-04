// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the implementation of the Dining Philosophers problem.

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <memory>  // For smart pointers
#include "Semaphore.h"
#include "Philosopher.h"

// Platform-specific command to clear the console screen
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"  // Windows command
#else
    #define CLEAR_SCREEN "clear"  // Linux/Unix command
#endif

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
        // Clear the console screen before displaying new status
        system(CLEAR_SCREEN);
        std::cout << "ID\tHUNGER\tSTATUS\t" << std::endl;

        // Iterate through each philosopher and display their status
        for (const auto& philosopher : philosophers) {
            std::cout << philosopher.get_id() << "\t"
                      << philosopher.get_hunger() << "\t"
                      << philosopher.get_state() << std::endl;
        }

        // Update status every second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char *argv[]) {
    int NUM_PHILOSOPHERS = 5;  // Default value

    // Check if a command-line argument for number of philosophers was passed
    if (argc > 1) {
        try {
            // Convert the argument to an integer
            NUM_PHILOSOPHERS = std::stoi(argv[1]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid argument (Using default)\n";
        }
    }

    // Ensure there is at least one philosopher
    NUM_PHILOSOPHERS = std::max(NUM_PHILOSOPHERS, 1);

    // Create semaphores representing forks (one for each philosopher)
    std::vector<std::unique_ptr<Semaphore>> forks;
    forks.reserve(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        // Each fork starts as available (value = 1)
        forks.push_back(std::make_unique<Semaphore>(1));
    }

    // Create philosophers and assign them to forks
    std::vector<Philosopher> philosophers;
    philosophers.reserve(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.emplace_back(
            i,  // Philosopher ID
            forks[i],  // Left fork (same index)
            // Right fork (next index, wraps around)
            forks[(i + 1) % NUM_PHILOSOPHERS],
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
    displayThread.join();  // Detach it so it runs independently

    // Wait for all philosopher threads to finish (WON'T HAPPEN)
    for (auto& philosopher : philosophersThreads) {
        philosopher.join();
    }

    // Should never reach this
    return 0;
}
