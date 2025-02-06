#include "drone.hpp"
#include "logger.hpp"
#include <iostream>
#include <cmath>

Drone::Drone()
    : posX(0.0), posY(0.0), altitude(0.0), battery(100.0), armed(false), airborne(false)
{
    Logger::log("Drone initialized. Ready to be armed.");
}

bool Drone::consumeBattery(double amount) {
    if (battery < amount) {
        Logger::log("Error: Insufficient battery. Operation aborted.");
        return false;
    }
    battery -= amount;
    return true;
}

bool Drone::arm() {
    if (armed) {
        Logger::log("Error: Drone is already armed.");
        return false;
    }
    if (airborne) {
        Logger::log("Error: Drone is airborne. Cannot arm while in flight.");
        return false;
    }
    armed = true;
    Logger::log("Drone armed.");
    return true;
}

bool Drone::disarm() {
    if (!armed) {
        Logger::log("Error: Drone is already disarmed.");
        return false;
    }
    if (airborne) {
        Logger::log("Error: Drone is airborne. Please land before disarming.");
        return false;
    }
    armed = false;
    Logger::log("Drone disarmed.");
    return true;
}

bool Drone::takeoff() {
    if (!armed) {
        Logger::log("Error: Drone must be armed to take off.");
        return false;
    }
    if (airborne) {
        Logger::log("Error: Drone is already airborne.");
        return false;
    }
    const double consumption = 10.0;
    if (!consumeBattery(consumption)) {
        Logger::log("Error: Battery too low for takeoff.");
        return false;
    }
    airborne = true;
    altitude = 1.0; // Default takeoff altitude
    Logger::log("Drone taking off. Altitude set to 1.0.");
    return true;
}

bool Drone::land() {
    if (!airborne) {
        Logger::log("Error: Drone is already on the ground.");
        return false;
    }
    const double consumption = 5.0;
    // Check if there is enough battery for a safe landing.
    if (battery < consumption) {
        Logger::log("Warning: Battery too low for safe landing!");
        battery = 0;       // Set battery to 0 in a crash landing scenario.
        airborne = false;  // Drone is no longer airborne.
        altitude = 0.0;    // Altitude drops to 0.
        armed = false;     // Drone is no longer operable.
        Logger::log("Drone has crash landed due to insufficient battery and is no longer operable.");
        return false;
    }
    // Sufficient battery for safe landing
    if (!consumeBattery(consumption)) {
        return false;
    }
    airborne = false;
    altitude = 0.0;
    Logger::log("Drone landing. Altitude set to 0.0.");
    return true;
}

bool Drone::move(double dx, double dy, double dz) {
    if (!armed) {
        Logger::log("Error: Drone is not armed. Please arm the drone before moving.");
        return false;
    }
    if (!airborne) {
        Logger::log("Error: Drone must be airborne to move.");
        return false;
    }
    double newAltitude = altitude + dz;
    if (newAltitude < 0) {
        Logger::log("Error: Cannot move below ground level.");
        return false;
    }
    
    double distance = std::abs(dx) + std::abs(dy) + std::abs(dz);
    const double consumption = 2.0 * distance;
    if (!consumeBattery(consumption)) {
        Logger::log("Error: Battery too low for movement.");
        return false;
    }
    
    posX += dx;
    posY += dy;
    altitude = newAltitude;
    
    Logger::log("Drone moved by deltas (" + std::to_string(dx) + ", " 
                + std::to_string(dy) + ", " + std::to_string(dz) + ").");
    return true;
}

bool Drone::hover() {
    if (!armed) {
        Logger::log("Error: Drone is not armed. Please arm the drone before hovering.");
        return false;
    }
    if (!airborne) {
        Logger::log("Error: Drone must be airborne to hover.");
        return false;
    }
    const double consumption = 2.0;
    if (!consumeBattery(consumption)) {
        Logger::log("Error: Battery too low for hovering.");
        return false;
    }
    Logger::log("Drone is hovering.");
    return true;
}

void Drone::printStatus() const {
    std::cout << "Drone Status:" << std::endl;
    std::cout << " Position: (" << posX << ", " << posY << ")" << std::endl;
    std::cout << " Altitude: " << altitude << std::endl;
    std::cout << " Battery: " << battery << "%" << std::endl;
    std::cout << " Armed: " << (armed ? "Yes" : "No") << std::endl;
    std::cout << " Airborne: " << (airborne ? "Yes" : "No") << std::endl;
}

void Drone::printBattery() const {
    std::cout << "Battery Level: " << battery << "%" << std::endl;
}

double Drone::getPosX() const {
    return posX;
}

double Drone::getPosY() const {
    return posY;
}

double Drone::getAltitude() const {
    return altitude;
}

double Drone::getBattery() const {
    return battery;
}

bool Drone::isAirborne() const {
    return airborne;
}

bool Drone::isArmed() const {
    return armed;
}