#pragma once
#include <string>
#include "drone.hpp"

// Processes user input commands and executes corresponding drone operations.
// Returns false if the command indicates exit, otherwise true.
bool processCommand(const std::string &command, Drone &drone); 