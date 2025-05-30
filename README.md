# SO2 Project: Dining Philosophers Problem

## Overview

This project is an implementation of the classic synchronization problem the **"Dining Philosophers Problem"** using **C++20**, multithreading, **semaphores**, and **mutexes**. The project simulates philosophers who alternate between thinking and eating while sharing limited resources (forks).

The implementation ensures:

* Avoidance of **deadlocks**.
* Prevention of **thread starvation**.
* Real-time tracking of philosopher status via a console-based display.

Inspired by the solution proposed by **Edsger Dijkstra**, this approach avoids the deadlock condition by using a hybrid semaphore strategy and ensures responsiveness in resource acquisition.

## Releases

* **Older Release**: The initial version with a simpler implementation.
* **Newer Release**: Adds more realistic approach of `think()` and `eat()` methods with improved synchronization.

## Problem Description

The Dining Philosophers Problem is an example in concurrent algorithm design. It involves:

* Five philosophers sitting at a table.
* One fork between each pair.
* Each philosopher must use two forks (left and right) to eat.

### Deadlock Conditions

To avoid **deadlocks**, one or more of this conditions must be implemented:

1. Each fork is used by only one philosopher at a time.
2. A philosopher cannot hold one fork while waiting for the other (if philosopher cannot take second fork the first has to be released).
3. A fork cannot be forcibly taken from a philosopher.
4. A closed chain it happens when each holds one fork and waits for another (second point prevents that).
5. Adding a watcher (waiter) for the philosophers that's going to be distributing tasks.

> I've implmented the point (1,2,3) which allows a philosopher to acquire both forks and not cause a deadlock.

References:
* [Wikipedia - Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* [GeeksForGeeks - Dining Philosopher Problem using Semaphores](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/)

## Implementation Details

### Structure

* `main.cpp`: Handles initialization, philosopher creation, and status display.
* `Philosopher.cpp/.h`: Defines philosopher behavior and hunger logic.
* `Semaphore.cpp/.h`: Custom semaphore class for fork synchronization using mutexes.

### Behavior

Each philosopher:

* Thinks for a random amount of time (1–3 seconds).
* Gets hungry and attempts to eat.
* Tries to acquire **both forks** (left, then right). If the right fork isn’t available, the left is released and the philosopher resumes thinking.
* If successful, eats (1–3 seconds), resets hunger, and releases forks.
* Dies if hunger reaches the `MAX_HUNGER` threshold.

The display updates every second to show the state (`THINKING`, `EATING`, or `DEAD`) of each philosopher.

### Concurrency

* **std::thread**: For philosopher lifecycle and display loop.
* **std::mutex + std::condition\_variable**: The `Semaphore` class synchronization mechanism.

## Building

### Requirements

* **Compiler**: `g++` supporting C++20
* **Build Tools**: `make` or `cmake`

### Build Steps

#### Option 1: Using `make`

```bash
make
```

#### Option 2: Using `cmake`

```bash
cmake .
make
```

### Run

To run the compiled program:

```bash
./DiningPhilosophers [number_of_philosophers]
```

> If no argument is provided, the default is **5 philosophers**.

## Example Output

```
ID      HUNGER  STATUS
0       3       THINKING
1       0       EATING
2       4       THINKING
3       10      DEAD
4       2       THINKING
```

# Multithreaded Chat Server

### TO BE CONTINUED

Nothing here at the moment
