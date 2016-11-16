set( UNIT_TESTS tokenizer.tests.cpp )

# Download and unpack googletest at configure time
# see https://crascit.com/2015/07/25/cmake-gtest/
# copy the CMakeLists.txt.in to build area as CMakeLists.txt
configure_file( CMakeLists.txt.in ${TEST_OUTPUT_DIRECTORY}/googletest-download/CMakeLists.txt )
# we need to execute the build steps at config time so that
# the tests can find the gtest libraries when they configure
execute_process( COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${TEST_OUTPUT_DIRECTORY}/googletest-download )
execute_process( COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${TEST_OUTPUT_DIRECTORY}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory( ${TEST_OUTPUT_DIRECTORY}/googletest-src
                 ${TEST_OUTPUT_DIRECTORY}/googletest-build )

# these steps compile and link the unit-tests executable
add_test( all unit-tests ) # gives us a make test all target
add_executable( unit-tests test-main.cpp ${SOURCE_FILES} ${UNIT_TESTS} )
target_link_libraries( unit-tests gtest gmock )
