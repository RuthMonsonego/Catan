#pragma once

#include <vector>
#include <memory>
#include "Resource.h"
#include "Coordinate.h"
#include "SettlementPoints.h"

class Tile {
private:
    std::shared_ptr<Resource> resource;

public:
    std::vector<std::vector<Coordinate>> coordinates;

    Tile(std::shared_ptr<Resource> resource);
    std::shared_ptr<Resource> getResource();
    void setResource(std::shared_ptr<SettlementPoints> newSettlementPoint);
};
