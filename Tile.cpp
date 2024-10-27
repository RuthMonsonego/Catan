#include "Tile.h"

Tile::Tile(std::shared_ptr<Resource> resource) {
    this->resource = resource;
    coordinates.resize(5);
    for (int i = 0; i < 5; ++i) {
        coordinates[i].resize(5);
        for (int j = 0; j < 5; ++j) {
            coordinates[i][j] = Coordinate();
        }
    }
}

std::shared_ptr<Resource> Tile::getResource() {
    return resource;
}

void Tile::setResource(std::shared_ptr<SettlementPoints> newSettlementPoint) {
    resource = newSettlementPoint;
}
