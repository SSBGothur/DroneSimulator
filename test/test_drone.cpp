#include "drone.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

int main() {
    std::cout << "Running Drone tests..." << std::endl;
    
    Drone drone;
    // Verify initial state
    assert(drone.getPosX() == 0.0);
    assert(drone.getPosY() == 0.0);
    assert(drone.getAltitude() == 0.0);
    assert(drone.getBattery() == 100.0);
    assert(!drone.isAirborne());
    assert(!drone.isArmed());
    
    // Test arming functionality
    bool result = drone.arm();
    assert(result == true);
    assert(drone.isArmed() == true);
    
    // Re-arming should fail
    result = drone.arm();
    assert(result == false);
    
    // Test takeoff (drone must be armed)
    result = drone.takeoff();
    assert(result == true);
    assert(drone.isAirborne() == true);
    assert(drone.getAltitude() == 1.0);

    // Test move by (5, 0, 2)
    double batteryBefore = drone.getBattery();
    result = drone.move(5, 0, 2);
    assert(result == true);
    assert(drone.getPosX() == 5.0);
    // Altitude becomes: 1.0 (takeoff) + 2 = 3.0
    assert(drone.getAltitude() == 3.0);
    double distance = std::abs(5) + std::abs(0) + std::abs(2);
    assert(drone.getBattery() == batteryBefore - 2.0 * distance);

    // Test hovering
    batteryBefore = drone.getBattery();
    result = drone.hover();
    assert(result == true);
    assert(drone.getBattery() == batteryBefore - 2.0);

    // Test landing
    batteryBefore = drone.getBattery();
    result = drone.land();
    assert(result == true);
    assert(!drone.isAirborne());
    assert(drone.getAltitude() == 0.0);
    assert(drone.getBattery() == batteryBefore - 5.0);
    
    // Test disarming
    result = drone.disarm();
    assert(result == true);
    assert(!drone.isArmed());

    // Disarming when already disarmed should fail
    result = drone.disarm();
    assert(result == false);

    std::cout << "All Drone tests passed!" << std::endl;
    return 0;
} 