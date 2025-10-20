cmake_minimum_required(VERSION 3.10)
project(ClassInheritanceDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Prefer modern warnings
if (MSVC)
	add_compile_options(/W4 /permissive-)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(include)

add_executable(demo src/main.cpp src/BaseClass.cpp src/SubClass.cpp)

# Enable testing
enable_testing()

# Add a simple test to run the demo executable
add_test(NAME RunDemo COMMAND demo)