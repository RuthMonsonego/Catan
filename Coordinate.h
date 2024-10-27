#pragma once

#include <iostream>
#include <memory>
#include "MovingCarryingItem.h"

class Coordinate
{
    std::shared_ptr<MovingCarryingItem> terrestrial_item_ptr;
    std::shared_ptr<MovingCarryingItem> air_item_ptr;

public:
    Coordinate();

    std::shared_ptr<MovingCarryingItem> getTerrestrialItem();
    std::shared_ptr<MovingCarryingItem> getAirItem();

    void setTerrestrialItem(std::shared_ptr<MovingCarryingItem> terrestrial_item);
    void setAirItem(std::shared_ptr<MovingCarryingItem> air_item);

    ~Coordinate() = default;
};


