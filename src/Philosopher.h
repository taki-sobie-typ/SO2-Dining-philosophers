// Created by Patryk on 20.03.2025.
// Copyright 2025 Patryk patrykpietrzyk@protonmail.com
// This file contains the declaration of the Philosopher class.

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#pragma once
#include "Semaphore.h"
#include <string>
#include <random>

class Philosopher {
 private:
    int id;  // Unique identifier for the philosopher
    int hunger = 0;  // Hunger level of the philosopher
    bool isAlive = true;  // Flag indicating if the philosopher is active
    bool isEating = false;  // Flag indicating if the philosopher is eating
    Semaphore &leftFork;  // Reference to the left fork (semaphore)
    Semaphore &rightFork;  // Reference to the right fork (semaphore)
    int MAX_HUNGER;  // Maximum hunger level before starvation
    // Random number generation members
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

 public:
    Philosopher(int id, Semaphore &leftFork,
                Semaphore &rightFork, int MAX_HUNGER);  // Constructor

    void operator()();  // Main loop for philosopher behavior

    void think();  // Simulates thinking

    void eat();  // Simulates eating

    int get_hunger() const;  // Returns the hunger level

    int get_id() const;  // Returns the philosopher's ID

    bool get_isAlive() const;  // Checks if the philosopher is alive

    bool get_isEating() const;  // Checks if the philosopher is currently eating

    void set_isAlive(bool isAlive);  // Sets the philosopher's alive status

    std::string get_state() const;  // Returns the current state of the philosopher

    void increase_hunger();  // Increases hunger level

    void decrease_hunger();  // Decreases hunger level
};

#endif  // PHILOSOPHER_H
