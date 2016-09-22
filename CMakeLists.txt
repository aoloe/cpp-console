CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("console")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

ADD_DEFINITIONS("-std=c++14 -Wall")


ADD_EXECUTABLE (console
    main.cpp
    console.cpp
)
