#pragma once
#include "Object.h"
#include <vector>

class Monster : public Object
{
public:
	int calculateAC(const Monster& monster);
	int attack(const Monster& monster);
	void monster(Monster& monster, int damage);
};

