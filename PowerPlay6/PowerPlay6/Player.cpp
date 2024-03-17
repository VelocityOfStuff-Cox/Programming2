#include <iostream>
#include <random>
#include "Object.h"
#include "Monster.h"
#include "Player.h"

std::random_device seed;
std::default_random_engine engine(seed());

void Player::levelUp(Player& player)
{
	player.level++;
	std::normal_distribution<double> randomHealth(20.0 + player.level * 5, 5.0);
	player.health += std::max(1, (int)randomHealth(engine));

	std::normal_distribution<double> randomStrength(3.0 + player.level, 1.0);
	player.strength += std::max(1, (int)randomStrength(engine));

	std::normal_distribution<double> randomSp(3.0 + player.level, 1.0);
	player.sp += std::max(1, (int)randomSp(engine));

	//grab new item.
	std::uniform_int_distribution<int> randomItem(0, (int)Item::Type::numTypes - 1);
	std::normal_distribution<double> randomBonus((double)player.level, (double)player.level / 2);
	Item found{ (Item::Type)randomItem(engine), std::max(1, (int)randomBonus(engine)) };

	std::cout << "You found a ";
	printItem(found);
	std::cout << "!!!!" << std::endl;
	if (
		auto haveOne{ player.inventory.find(Item::getType(found) };
		haveOne == player.inventory.end()
		|| Item::getBonusValue(player.inventory[Item::getType(found)]) < Item::getBonusValue(found)
		)
	{
		std::cout << "You keep the shiny new toy!" << std::endl;
		player.inventory[Item::getType(found)] = found;
	}
	else
	{
		std::cout << "You toss aside the ugly old thing!" << std::endl;
	}
}

int Player::calculateAC(const Player& player)
{
	int AC{ 0 };
	if (auto armor{ player.inventory.find(Item::Type::armor) }; armor != player.inventory.end())
	{
		AC += Item::getBonusValue(armor);
	}
	if (auto shield{ player.inventory.find(Item::Type::shield) }; shield != player.inventory.end())
	{
		AC += Item::getBonusValue(shield);
	}
	return AC;
}

int Player::attack(const Player& player)
{
	int potentialDamage{ player.strength };
	if (auto sword{ player.inventory.find(Item::Type::sword) }; sword != player.inventory.end())
	{
		potentialDamage += Item::getBonusValue(sword);
	}
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	printName(player);
	std::cout << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

void Player::defend(Player& object, int damage)
{
	std::normal_distribution<double> defense(calculateAC(object), 1.0 / object.level);
	damage = std::max(0, damage - (int)defense(engine));
	std::cout << damage << " damage to ";
	printName(object);
	std::cout << "!!!" << std::endl;
	object.health -= damage;
}

void Player::heal(Player& player)
{
	if (player.sp >= 2)
	{
		std::normal_distribution<double> randomHeal(player.strength, 3.0);
		int  amountHealed{ std::max(1, (int)randomHeal(engine)) };
		printName(player);
		std::cout << " is healed by " << amountHealed << "hp!" << std::endl;
		player.health += amountHealed;
		player.sp -= 2;
	}
	else
	{
		std::cout << "You don't have enough spell points to heal" << std::endl;
	}
}
