#pragma once

#include <iostream>
#include <string>

class MovingCarryingItem
{
	int kind;
	int contemporaryCarrying[4];
public:
	MovingCarryingItem(int k);

	int getKindCode();
	int* getContemporaryCarrying();
	void addAmountToContemporaryCarrying(std::string resource, int amount);
	int getAmountStayPlace(int index);
	int getAmountInStorage(int index);
	void setAmountInStorage(int index, int amount);
};