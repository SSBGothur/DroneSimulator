#include "commands.hpp"
#include "drone.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Running Command tests..." << std::endl;
    Drone drone;

    // Test "arm" command
    bool cont = processCommand("arm", drone);
    assert(cont == true);
    assert(drone.isArmed() == true);

    // Test "takeoff" command
    cont = processCommand("takeoff", drone);
    assert(cont == true);
    assert(drone.isAirborne() == true);
    assert(drone.getAltitude() == 1.0);

    // Test "move" command with delta values: move 3 -2 4
    cont = processCommand("move 3 -2 4", drone);
    assert(cont == true);
    // Expected: posX = 3, posY = -2, altitude = 1.0 + 4 = 5.0
    assert(drone.getPosX() == 3.0);
    assert(drone.getPosY() == -2.0);
    assert(drone.getAltitude() == 5.0);

    // Test "hover" command
    cont = processCommand("hover", drone);
    assert(cont == true);

    // Test "status" command (output only, state remains unchanged)
    double battery_before = drone.getBattery();
    cont = processCommand("status", drone);
    assert(cont == true);
    assert(drone.getBattery() == battery_before);

    // Test "battery" command (should display battery level)
    battery_before = drone.getBattery();
    cont = processCommand("battery", drone);
    assert(cont == true);
    assert(drone.getBattery() == battery_before);

    // Test "land" command
    cont = processCommand("land", drone);
    assert(cont == true);
    assert(!drone.isAirborne());
    assert(drone.getAltitude() == 0.0);

    // Test "disarm" command after landing
    cont = processCommand("disarm", drone);
    assert(cont == true);
    assert(!drone.isArmed());

    // Test an unknown command
    cont = processCommand("fly", drone);  // Should log an error message.
    assert(cont == true);

    // Test "exit" command to signal termination.
    cont = processCommand("exit", drone);
    assert(cont == false);

    std::cout << "All Command tests passed!" << std::endl;
    return 0;
} 