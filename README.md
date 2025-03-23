# SO2 Project: Dining Philosophers Problem

## Releases
There are two releases of the project:
- **Older Release**: The initial version with a simpler implementation.
- **Newer Release**: A more realistic approach to the `thinking()` and `eating()` methods, with modifications to the `Semaphore` class for better synchronization.

## Building

### Requirements
- **C++ Version**: C++20
- **Tools**:
    - `make` or `cmake`
    - `g++` compiler

### Steps
1. Clone or download the project to your local machine.
2. Open a terminal in the project folder.
3. Run the following command to build the project:
   ```bash
   make
   ```
   or, if you're using `cmake`:
   ```bash
   cmake .
   make
   ```

This will compile the project, using the necessary C++20 features and the provided Makefile or CMake configuration.