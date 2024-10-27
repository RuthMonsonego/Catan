#pragma once

#include <string>
#include <memory>
#include "MovementStrategy.h"

class Vehicle {
private:
    std::string imageName;
    int x;
    int y;
    std::shared_ptr<MovementStrategy> strategy;
    bool isGround;

public:
    Vehicle(const std::string& imageName, int x, int y, std::shared_ptr<MovementStrategy> strategy)
        : imageName(imageName), x(x), y(y), strategy(strategy) {}

    const std::string& getImageName() const {
        return imageName;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void move() {
        strategy->move(x, y); 
    }

    bool isGroundVehicle() const {
        return isGround;
    }

    void handleCollision(Vehicle& other) {
        if (isCollidingWith(other)) {
            if (isGroundVehicle()) {
                x += 10; 
            }
        }
    }

private:
    bool isCollidingWith(const Vehicle& other) const {
        return (x == other.getX() && y == other.getY());
    }
};

