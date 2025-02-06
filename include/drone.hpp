#pragma once
#include <iostream>
#include <string>

class Drone {
    public:
        Drone();

        // Control methods for drone operation
        bool arm();
        bool disarm();
        bool takeoff();
        bool land();
        bool move(double dx, double dy, double dz);
        bool hover();

        // Print and status methods
        void printStatus() const;
        void printBattery() const;

        // Getter methods for testing and inspection
        double getPosX() const;
        double getPosY() const;
        double getAltitude() const;
        double getBattery() const;
        bool isAirborne() const;
        bool isArmed() const;

    private:
        double posX;       // X-coordinate in 3D space
        double posY;       // Y-coordinate in 3D space
        double altitude;   // Altitude (Z-coordinate)
        double battery;    // Battery level (0-100%)
        bool armed;        // Drone armed state
        bool airborne;     // Drone airborne status

        // Consumes the specified battery amount if available.
        bool consumeBattery(double amount);
};