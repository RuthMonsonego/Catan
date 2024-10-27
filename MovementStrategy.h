#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

class MovementStrategy {
public:
    virtual void move(int& x, int& y) = 0;
};

#endif // MOVEMENTSTRATEGY_H
