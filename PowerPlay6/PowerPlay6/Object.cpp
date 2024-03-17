#include <iostream>
#include <random>
#include <algorithm>
#include "Object.h"
#include "Item.h"
#include "monster.h"

std::random_device seed;
std::default_random_engine engine(seed());

void Object::displayBattle(const Object& player, const std::vector<Object>& monsters)
{
	printName(player);
	std::cout << " h:" << player.health << std::endl;
	std::for_each(player.inventory.begin(), player.inventory.end(), [](std::pair<Item::Type, Item> item)
		{
			std::cout << "  ";
			printItem(item.second);
			std::cout << std::endl;
		});
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
			{
				std::cout << "   " << i << ". ";
				printName(monster);
				std::cout << " h:" << monster.health << std::endl;
				i++;
			});
	}
}

std::vector<Object> Object::createMonsters(const Object& player)
{
	std::normal_distribution<double> randomNumMonsters((double)player.level, player.level / 2.0);
	std::vector<Object> monsters(std::max(1, (int)randomNumMonsters(engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			//set level based on player level
			std::normal_distribution<double> monsterLevel((float)player.level, player.level / 4.0);
			int level{ std::max(1, (int)monsterLevel(engine)) };

			std::uniform_int_distribution<int> monsterType(1, (int)Object::Type::numTypes - 1);
			Object::Type name{ (Object::Type)monsterType(engine) };

			double strengthVariance{ 0.0 };
			double healthVariance{ 0.0 };
			switch (name)
			{
			case Object::Type::slime:
				strengthVariance = level * 1.5;
				healthVariance = level * 1.25;
				break;
			case Object::Type::orc:
				strengthVariance = level * 2.0;
				healthVariance = (long long)level * level * 1.25;
				break;
			case Object::Type::sprite:
				strengthVariance = level * 1.75;
				healthVariance = level;
				break;
			case Object::Type::dragon:
				strengthVariance = level * 6.0;
				healthVariance = (long long)level * level * 3.0;
				break;
			}
			std::normal_distribution<double> randomStrength(strengthVariance, level / 4.0);
			std::normal_distribution<double> randomHealth(healthVariance * 5, level / 2.0);

			Object monster(
				{
					name,
					std::max(1, (int)randomStrength(engine)),
					std::max(1, (int)randomHealth(engine)),
					level,
					{}
				});
			return monster;
		});
	return monsters;
}

void Object::monsterAttack(Object& player, const std::vector<Object>& monsters)
{

	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&](const Object& monster)
		{
			std::bernoulli_distribution willAttack(.75);
			if (willAttack(engine))
			{
				printName(monster);
				std::cout << " attacks!" << std::endl;
				Player::defend(player, Monster::attack(monster));
			}
			else
			{
				printName(monster);
				std::cout << " twiddles its thumbs" << std::endl;
			}
		});
}

void Object::playerAttack(const Object& player, std::vector<Object>& monsters)
{
	std::cout << "Which Monster: ";
	int monsterNum{ 0 };
	std::cin >> monsterNum;
	if (monsterNum > 0 && monsterNum <= monsters.size())
	{
		Monster::defend(monsters[monsterNum - 1], Player::attack(player));
	}
}

void Object::printName(const Object& object)
{
	std::cout << "L:" << object.level << " ";
	switch (object.name)
	{
	case Object::Type::player:
		std::cout << "Player";
		break;
	case Object::Type::slime:
		std::cout << "Slime";
		break;
	case Object::Type::orc:
		std::cout << "Orc";
		break;
	case Object::Type::sprite:
		std::cout << "Sprite";
		break;
	case Object::Type::dragon:
		std::cout << "Dragon";
		break;
	}
}

void Object::printItem(const Item& item)
{
	switch (Item::getType(item))
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

int Object::getHealth(Object& object)
{
	return object.health;
}

void Object::operator<<(const Object object)
{
	std::cout << object.level << "\n"
		<< object.health << std::endl;;

	switch (object.name)
	{
	case Object::Type::player:
		std::cout << "Player";
		break;
	case Object::Type::slime:
		std::cout << "Slime";
		break;
	case Object::Type::orc:
		std::cout << "Orc";
		break;
	case Object::Type::sprite:
		std::cout << "Sprite";
		break;
	case Object::Type::dragon:
		std::cout << "Dragon";
		break;
	}
}

void Object::heal(Object& object)
{
	std::normal_distribution<double> randomHeal(object.strength, 3.0);
	int  amountHealed{ std::max(1, (int)randomHeal(engine)) };
	printName(object);
	std::cout << " is healed by " << amountHealed << "hp!" << std::endl;
	object.health += amountHealed;
}

void Object::bringOutYourDead(std::vector<Object>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](Object& monster)
			{
				if (monster.health <= 0)
				{
					printName(monster);
					std::cout << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());

}

