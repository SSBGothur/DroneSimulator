#include "drone.hpp"
#include "commands.hpp"
#include "logger.hpp"
#include <iostream>
#include <string>

int main() {
    Drone drone;
    std::string input;

    Logger::log("Welcome to Drone Simulator!");
    Logger::log("Enter commands (arm, disarm, takeoff, land, move, hover, status, battery, exit).");

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input.empty()) continue;
        bool continueLoop = processCommand(input, drone);
        if (!continueLoop) {
            break;
        }
    }

    Logger::log("Drone Simulator terminated.");
    return 0;
} 