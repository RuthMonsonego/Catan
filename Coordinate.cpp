#include "Coordinate.h"
#include <iostream>
#include <memory>

using namespace std;

Coordinate::Coordinate() : terrestrial_item_ptr(nullptr), air_item_ptr(nullptr) { }

shared_ptr<MovingCarryingItem> Coordinate::getTerrestrialItem() {
	return terrestrial_item_ptr;
}

shared_ptr<MovingCarryingItem> Coordinate::getAirItem() {
	return air_item_ptr;
}

void Coordinate::setAirItem(shared_ptr<MovingCarryingItem> air_item) {
	if ((!air_item_ptr && air_item) || (!air_item && air_item_ptr)) {
		air_item_ptr = air_item;
	}
	else {
		throw std::logic_error("Car or truck cannot go there");
	}
}

void Coordinate::setTerrestrialItem(shared_ptr<MovingCarryingItem> terrestrial_item) {
	//if ((!terrestrial_item_ptr && terrestrial_item) || (!terrestrial_item && terrestrial_item_ptr)) {
		terrestrial_item_ptr = terrestrial_item;
	//}
	//else {
	//	throw std::logic_error("Vihacle or human cannot go there");
	//}
}