// Created by Patryk on 20.03.2025.
// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the implementation of the Philosopher class.

#include "Philosopher.h"
#include <chrono>
#include <thread>
#include <string>
#include <random>

Philosopher::Philosopher(
    int id,
    Semaphore &leftFork,
    Semaphore &rightFork,
    int MAX_HUNGER
) : id(id),
    leftFork(leftFork),
    rightFork(rightFork),
    MAX_HUNGER(MAX_HUNGER),
    gen(std::random_device {}()),  // Random number generator with a random seed
    dist(1, 3) {  // Distribution to generate values between 1 and 3
}

void Philosopher::operator()() {
    while (isAlive) {
        think();  // Philosopher thinks before eating
        increase_hunger();  // Hunger increases over time
        eat();  // Philosopher tries to eat
        decrease_hunger();  // Eating decreases hunger
    }
}

void Philosopher::think() {
    isEating = false;  // Philosopher is not eating while thinking
    const int thinkingTime = dist(gen);  // Generate a random number between 1 and 3
    std::this_thread::sleep_for(std::chrono::seconds(thinkingTime));  // Thinking time
}

void Philosopher::eat() {
    leftFork.wait();  // Acquire left fork
    rightFork.wait();  // Acquire right fork

    isEating = true;  // Philosopher starts eating

    const int thinkingTime = dist(gen);  // Generate a random number between 1 and 3
    std::this_thread::sleep_for(std::chrono::seconds(thinkingTime));  // Thinking time

    leftFork.signal();  // Release left fork
    rightFork.signal();  // Release right fork
}

int Philosopher::get_hunger() const { return hunger; }  // Returns current hunger level

int Philosopher::get_id() const { return id; }  // Returns philosopher ID

bool Philosopher::get_isAlive() const { return isAlive; }  // Checks if philosopher is alive

bool Philosopher::get_isEating() const { return isEating; }  // Checks if philosopher is eating

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
        hunger--;  // Reduce hunger after eating
    }
}
