// Created by Patryk on 20.03.2025.
// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the implementation of the Philosopher class.

#include "Philosopher.h"
#include <chrono>
#include <thread>
#include <string>
#include <random>
#include <memory>

Philosopher::Philosopher(
    int id,
    const std::unique_ptr<Semaphore>& leftFork,
    const std::unique_ptr<Semaphore>& rightFork,
    int MAX_HUNGER
) : id(id),
    leftFork(leftFork.get()),
    rightFork(rightFork.get()),
    MAX_HUNGER(MAX_HUNGER),
    gen(std::random_device {}()),  // Random number generator with a random seed
    dist(1, 3) {  // Distribution to generate values between 1 and 3
}

void Philosopher::operator()() {
    while (isAlive) {
        think();  // Thinks before eating
        eat();  // Tries to eat
    }
}

void Philosopher::think() {
    isEating = false;  // Philosopher is not eating while thinking

    // Generate a random number between 1 and 3
    const int thinkingTime = dist(gen);

    // Thinking time
    std::this_thread::sleep_for(std::chrono::seconds(thinkingTime));

    increase_hunger();  // Hunger increases over time
}

void Philosopher::eat() {
    // Only when hungry can eat
    if (hunger <= 1) {
        return;
    }

    // Try to acquire the left fork
    leftFork->wait();  // Block until left fork is available

    // Try to acquire the right fork
    if (!rightFork->try_wait()) {
        // Release left fork if right fork is unavailable
        leftFork->signal();
        return;  // Return to thinking if unable to acquire both forks
    }

    isEating = true;  // Philosopher starts eating

    // Generate a random number between 1 and 3
    const int eatingTime = dist(gen);

    // Eating time
    std::this_thread::sleep_for(std::chrono::seconds(eatingTime));

    decrease_hunger();  // Eating decreases hunger

    // Release both forks after eating
    leftFork->signal();
    rightFork->signal();
}

// Returns current hunger level
int Philosopher::get_hunger() const { return hunger; }

int Philosopher::get_id() const { return id; }  // Returns philosopher ID

// Checks if philosopher is alive
bool Philosopher::get_isAlive() const { return isAlive; }

// Checks if philosopher is eating
bool Philosopher::get_isEating() const { return isEating; }

void Philosopher::set_isAlive(bool isAlive) {
    this->isAlive = isAlive;  // Updates philosopher's alive status
}

std::string Philosopher::get_state() const {
    if (!isAlive) {
        return "DEAD";  // Philosopher has starved
    }
    if (isEating) {
        return "EATING";  // Philosopher is eating
    }
    return "THINKING";  // Philosopher is thinking
}

void Philosopher::increase_hunger() {
    if (hunger < MAX_HUNGER) {
        hunger++;  // Increment hunger level
    } else {
        isAlive = false;  // Philosopher dies if hunger exceeds max limit
    }
}

void Philosopher::decrease_hunger() {
    if (hunger > 0) {
        hunger = 0;  // Reduce hunger after eating
    }
}
