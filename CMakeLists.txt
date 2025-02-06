cmake_minimum_required(VERSION 3.10)
project(DroneSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(lib)

# Main executable sources
set(SRC_FILES
    src/main.cpp
    src/drone.cpp
    src/commands.cpp
    lib/logger.cpp
)

add_executable(DroneSimulator ${SRC_FILES})

# Enable testing
enable_testing()

# Unit test for Drone functionality
add_executable(TestDrone test/test_drone.cpp src/drone.cpp lib/logger.cpp)
add_test(NAME TestDrone COMMAND TestDrone)

# Unit test for Command processing
add_executable(TestCommands test/test_commands.cpp src/commands.cpp src/drone.cpp lib/logger.cpp)
add_test(NAME TestCommands COMMAND TestCommands) 