#ifndef HELICOPTERMOVEMENTSTRATEGY_H
#define HELICOPTERMOVEMENTSTRATEGY_H

#include "MovementStrategy.h"

class HelicopterMovementStrategy : public MovementStrategy {
public:
    void move(int& x, int& y) override {
        // Implement helicopter movement logic here
        y -= 10;
    }
};

#endif // HELICOPTERMOVEMENTSTRATEGY_H
