CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT("console")

# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

#ADD_DEFINITIONS("-std=c++14 -Wall")
set (CMAKE_CXX_STANDARD 14)


ADD_EXECUTABLE (console
    main.cpp
    console.cpp
)
