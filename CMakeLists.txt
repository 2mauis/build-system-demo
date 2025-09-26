cmake_minimum_required(VERSION 3.10)
project(ClassInheritanceDemo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(demo src/main.cpp src/BaseClass.cpp src/SubClass.cpp)