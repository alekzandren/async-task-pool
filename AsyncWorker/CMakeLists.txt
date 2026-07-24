cmake_minimum_required(VERSION 3.26)
project(. CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

find_package(Threads REQUIRED)

if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -O3)
endif()

add_executable(AsyncWorker
        src/main.cpp
        src/TaskQueue.cpp
        include/TaskQueue.hpp
)

target_link_libraries(AsyncWorker PRIVATE Threads::Threads)