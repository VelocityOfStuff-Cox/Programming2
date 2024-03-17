#pragma once
#include <vector>
#include <map>
#include "Object.h"
#include "Item.h"

class Player : public Object
{
private:
	int sp{ 0 };
	
public:
	void levelUp(Player& player);
	int calculateAC(const Player& player);
	int attack(const Player& object);
	void defend(Player& object, int damage);
	void heal(Player& player);
};

