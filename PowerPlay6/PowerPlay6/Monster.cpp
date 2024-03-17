#include <iostream>
#include <random>
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::random_device seed;
std::default_random_engine engine(seed());

int Monster::calculateAC(const Monster& monster)
{
	double ACVarience{ 0 };
	switch (monster.name)
	{
	case Monster::Type::slime:
		ACVarience = monster.level / 2.0 ;
	case Monster::Type::orc:
		ACVarience = monster.level * 1.5 ;
	case Monster::Type::sprite:
		ACVarience = 0.0;
	case Monster::Type::dragon:
		ACVarience = monster.level * 3.0 ;
	default:
		break;
	}

	std::normal_distribution<double> randomAC(monster.level, ACVarience);

	int AC{ randomAC(engine) };
	return AC;
}

int Monster::attack(const Monster& monster)
{
	int potentialDamage{ monster.strength };
	std::normal_distribution<double> damageDealt(potentialDamage, 2.0);

	printName(monster);
	std::cout << " deals ";
	return std::max(1, (int)damageDealt(engine));
}

void Monster::monster(Monster& monster, int damage)
{
	std::normal_distribution<double> defense(calculateAC(monster), 1.0 / monster.level);
	damage = std::max(0, damage - (int)defense(engine));
	std::cout << damage << " damage to ";
	printName(monster);
	std::cout << "!!!" << std::endl;
	monster.health -= damage;
}
