#ifndef PERSONMOVEMENTSTRATEGY_H
#define PERSONMOVEMENTSTRATEGY_H

#include "MovementStrategy.h"

class PersonMovementStrategy : public MovementStrategy {
public:
    void move(int& x, int& y) override {
        // Implement person movement logic here
        x -= 10;
    }
};

#endif // PERSONMOVEMENTSTRATEGY_H
