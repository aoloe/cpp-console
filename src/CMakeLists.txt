# or better "cmake -DCMAKE_BUILD_TYPE=Debug .."
set(CMAKE_BUILD_TYPE Debug)

#ADD_DEFINITIONS("-std=c++14 -Wall")
set (CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
    console.cpp
)
ADD_LIBRARY(console
    ${SOURCE_FILES}
)
