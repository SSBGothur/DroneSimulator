#include "commands.hpp"
#include "logger.hpp"
#include <sstream>
#include <iostream>
#include <string>

bool processCommand(const std::string &input, Drone &drone) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command == "exit") {
        Logger::log("Exiting Drone Simulator.");
        return false;
    } else if (command == "arm") {
        drone.arm();
    } else if (command == "disarm") {
        drone.disarm();
    } else if (command == "takeoff") {
        drone.takeoff();
    } else if (command == "land") {
        drone.land();
    } else if (command == "move") {
        double dx, dy, dz;
        iss >> dx >> dy >> dz;
        if (iss.fail()) {
            Logger::log("Error: Invalid move command. Usage: move <dx> <dy> <dz>");
        } else {
            drone.move(dx, dy, dz);
        }
    } else if (command == "hover") {
        drone.hover();
    } else if (command == "status") {
        drone.printStatus();
    } else if (command == "battery") {
        drone.printBattery();
    } else {
        Logger::log("Error: Unknown command \"" + command + "\".");
    }
    return true;
} 