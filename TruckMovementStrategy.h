#ifndef TRUCKMOVEMENTSTRATEGY_H
#define TRUCKMOVEMENTSTRATEGY_H

#include "MovementStrategy.h"

class TruckMovementStrategy : public MovementStrategy {
public:
    void move(int& x, int& y) override {
        // Implement truck movement logic here
        y += 10;
    }
};

#endif // TRUCKMOVEMENTSTRATEGY_H
