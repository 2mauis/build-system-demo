cmake_minimum_required(VERSION 3.10)
project(ClassInheritanceDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(demo src/main.cpp src/BaseClass.cpp src/SubClass.cpp)

# Enable testing
enable_testing()

# Add a simple test to run the demo executable
add_test(NAME RunDemo COMMAND demo)