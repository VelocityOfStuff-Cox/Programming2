#include <iostream>
#include "Item.h"

Item::Type Item::getType(Item& item)
{
    return item.clasification;
}

int Item::getBonusValue(Item& item)
{
    return item.bonusValue;
}

void Item::operator<<(Item item)
{
	switch (item.clasification)
	{
	case Item::Type::armor:
		std::cout << "Armor";
		break;
	case Item::Type::shield:
		std::cout << "Shield";
		break;
	case Item::Type::sword:
		std::cout << "Sword";
		break;
	}
	std::cout << "+" << Item::getBonusValue(item);
}

bool Item::operator<(Item item, Item otherItem)
{
	if (item.getBonusValue(item) < otherItem.getBonusValue(otherItem))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Item::operator+=(Item item, int increase)
{
	return item.getBonusValue(item) + increase;
}
