#pragma once
#include <map>
#include <vector>
#include "Item.h"

class Object
{
public:
	enum class Type { player, slime, orc, sprite, dragon, numTypes };

	std::vector<Object> createMonsters(const Object& player);
	void monsterAttack(Object& player, const std::vector<Object>& monsters);
	void bringOutYourDead(std::vector<Object>& monsters);
	void playerAttack(const Object& player, std::vector<Object>& monsters);
	void displayBattle(const Object& player, const std::vector<Object>& monsters);

	void printName(const Object& object);
	void printItem(const Item& item);

	int getHealth(Object& object);

	void operator<<(const Object object);
	
protected:
	Type name;
	int strength{ 0 };
	int health{ 0 };
	int level{ 0 };
	std::map<Item::Type, Item> inventory;
};

