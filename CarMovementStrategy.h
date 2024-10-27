#ifndef CARMOVEMENTSTRATEGY_H
#define CARMOVEMENTSTRATEGY_H

#include "MovementStrategy.h"

class CarMovementStrategy : public MovementStrategy {
public:
    void move(int& x, int& y) override {
        x += 10; // Example movement for car (vertical movement)
    }
};

#endif // CARMOVEMENTSTRATEGY_H
