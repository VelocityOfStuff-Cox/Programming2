#pragma once

class Item
{
public:
	enum class Type { sword, armor, shield, numTypes };
private:
	Type clasification;
	int bonusValue;
public:
	Type getType(Item& item);
	int getBonusValue(Item& item);
	void operator<<(Item item);
	bool operator<(Item item, Item otherItem);
	int operator+=(Item item, int increase);
};