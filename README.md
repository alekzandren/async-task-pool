# C++23 Task Engine

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg?style=flat-square&logo=cplusplus&logoColor=white)](https://en.cppreference.com/w/cpp/23)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg?style=flat-square)](https://github.com/alekzandren/cpp-task-engine)
[![Version](https://img.shields.io/badge/Version-1.0.0-blueviolet.svg?style=flat-square)](https://github.com/alekzandren/cpp-task-engine)
[![CMake](https://img.shields.io/badge/CMake-3.26%2B-064F8C.svg?style=flat-square&logo=cmake&logoColor=white)](https://cmake.org/)
[![Category: Concurrency](https://img.shields.io/badge/Category-Concurrency%20%7C%20RAII-darkgreen.svg?style=flat-square)](https://github.com/alekzandren/cpp-task-engine)

**Task Engine** is a lightweight, high-performance, and cross-platform asynchronous Worker Pool implementation written in modern **C++23**. 

Designed with a focus on type safety, concurrency safety, **RAII** resource management, and zero external dependencies beyond the standard library.

---

## Key Features

* **Modern C++23 Standard:** Leverages standard concurrency features such as `std::jthread`, cancellation tokens (`std::stop_token`), and thread-safe streaming via `std::osyncstream`.
* **RAII & Exception Safety:** Automatic thread stop requests and graceful join handling upon out-of-scope destruction (no leaked resource handles or hanging threads).
* **Zero External Dependencies:** Built purely using the standard C++ library (STL).
* **Cross-Platform Support:** Ready-to-use CMake configuration for Linux, Windows (MSVC / MinGW), and macOS (Clang).
* **Thread-Safe Queue:** Concurrent task dispatching powered by `std::mutex` and `std::condition_variable_any`.

---

## Prerequisites

To build and run this project, ensure you have:

* **C++23 Compliant Compiler:**
  * GCC 13+
  * Clang 16+
  * MSVC 19.35+ (Visual Studio 2022)
* **CMake:** Version 3.26 or higher
* **IDE (Optional):** CLion, VS Code, or Visual Studio 2022

---

## Quick Start

### Build via Command Line (CLI)

```bash
# 1. Clone the repository
git clone [https://github.com/your-username/cpp-task-engine.git](https://github.com/your-username/cpp-task-engine.git)
cd cpp-task-engine

# 2. Configure the project using CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 3. Build the executable
cmake --build build --config Release

# 4. Run the program
./build/AsyncWorker
```

---

## Setup in CLion
Open the project folder in CLion (`File` -> `Open`).
Verify that your CMake Profile (`Settings` -> `Build, Execution, Deployment` -> `CMake`) uses a toolchain supporting C++23.
Click the Run button (`Shift + F10` / `Control + R`).

---

## Usage Example
```C++
#include "TaskQueue.hpp"
#include <iostream>
#include <syncstream>

int main() {
    // Initialize a pool with 4 worker threads
    ThreadPool pool(4);

    // Enqueue an asynchronous task
    pool.enqueue([]() {
        std::osyncstream(std::cout) << "Task executed on thread: " 
                                    << std::this_thread::get_id() << "\n";
    });

    // ThreadPool destructor gracefully stops all workers on scope exit
    return 0;
}
```

## Project Structure
```Plaintext
cpp-task-engine/
├── CMakeLists.txt         # Main CMake build script
├── include/
│   └── TaskQueue.hpp      # ThreadPool interface and task definitions
├── src/
│   ├── TaskQueue.cpp      # Worker loop & synchronization logic
│   └── main.cpp           # Entry point and usage demonstration
├── .gitignore
└── README.md
```

---

## License
This project is open-source and available under the MIT License.

