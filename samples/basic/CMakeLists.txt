include_directories(${CONSOLE_SOURCES_DIR})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

ADD_EXECUTABLE (console-basic
    main.cpp
    ${CONSOLE_SOURCES}
)
