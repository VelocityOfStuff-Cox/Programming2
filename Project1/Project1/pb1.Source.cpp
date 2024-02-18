/*
* Developer: Isabella Cox
* Contact: velocityofstuff1@gmail.com
* Version: 1.3
* Creation Date: 1/20/2024
* Version Creation Date: 2/3/2024
* Written with Visual Studio, assistance from learncpp.com, and cplusspluss.com for function syntax
*/

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

struct Object
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
	bool dead{ 0 };
};

void displayBattle(Object player, std::vector<Object> monsters);
void playerAttack(Object& player, Object& monsters, std::mt19937& mt);
void monsterAttack(Object& player, Object& monster, std::mt19937& mt);
int attack(Object& attacker, std::mt19937& mt);
int defend(Object& defender, int damage);
int heal(Object& creature, std::mt19937& mt);

int main()
{
	//Mersenne twister set up for uncertain values
	std::mt19937 mt{ std::random_device{}() };
	std::normal_distribution randStr{ 5.0, 1.0 };
	std::normal_distribution randHp{ 30.0, 5.0 };

	//Player Character with random strength and health values
	Object player{};
	player.name = "Gongalor";
	player.strength = std::max(1, int(randStr(mt)));
	player.health = std::max(1, int(randHp(mt)));

	//creates one to three entites called "monsters" for the player to fight
	std::uniform_int_distribution ud{ 1, 3 };
	int spawn{ ud(mt) };
	std::vector<Object> monsters;
	for (int i{ 0 }; i < spawn; i++)
	{
		//intitializes the monster for the current itteration of the loop
		//strength and health are random like the player
		std::string monsterName{ "Monster " + std::to_string(i + 1) };
		monsters.push_back(Object());
		monsters.back().name = monsterName;
		monsters.back().strength = std::max(1, int(randStr(mt)));;
		monsters.back().health = std::max(1, int(randHp(mt)));
	}

	std::cout << "Fight the Monsters" << "\n" << std::endl;

	//Game loop
	while (player.health > 0 && monsters.size() > 0)
	{
		displayBattle(player, monsters);

		//initializes the user input variable
		int userInput{ 0 };
		std::cin >> userInput;

		//Player's turn 
		switch (userInput)
		{
		case 1:

			std::cout << "Enter the number of the monster you wish to attack" << std::endl;

			std::cin >> userInput;

			//Input validated combat Player wastes turn on invalid targets
			if (userInput > 0 && userInput <= monsters.size() && !monsters.at(userInput - 1).dead)
			{
				playerAttack(player, monsters.at(userInput - 1), mt);
			}
			else
			{
				std::cout << "Please select a valid target" << std::endl;
			}
			break;
		case 2:
			//heals player
			player.health = heal(player, mt);
			break;
		default:
			std::cout << "Please input an appropriate value." << std::endl;
			break;
		}

		for (int i{ 0 };i < monsters.size(); i++)
		{
			//monster will randomly attack or heal
			std::bernoulli_distribution chance(0.75);
			bool attackHeal{ chance(mt) };
			if (attackHeal == 1)
			{
				monsterAttack(player, monsters.at(i), mt);
			}
			else
			{
				monsters.at(i).health = heal(monsters.at(i), mt);
			}
		}

		system("PAUSE");
		system("CLS");
	}

	//possible game ove conditions
	if (player.health <= 0)
	{
	std::cout << "You fell to the monsters :( Thank you for playing!" << std::endl;
	}
	else if (monsters.size() == 0)
	{
		std::cout << "You defeated the monsters! Thank you for playing!" << std::endl;
	}
	else if (player.health < 0 && monsters.size() == 0)
	{
		std::cout << "You and the monsters defeated eachother :l Thank you for playing!" << std::endl;
	}
	else
	{
		std::cout << "Unknown case. please contact Developer with details. velocityofstuff1@gmail.com" << std::endl;
	}

}

void displayBattle(Object player, std::vector<Object> monsters)
{
	std::cout << player.name
		<< "\nHealth: " << player.health
		<< "\nStrength: " << player.strength 
		<< "\n" << std::endl;

	for (int i{ 0 }; i < monsters.size(); i++)
	{
		if (monsters.at(i).health > 0)
		{
			//prints living monsters
			std::cout << i + 1 << ". " << monsters.at(i).name
				<< "\nHealth: " << monsters.at(i).health
				<< "\nStrength: " << monsters.at(i).strength 
				<< "\n" << std::endl;
		}
		else
		{
			//prints dead monsters
			std::cout << i + 1 << ". " << monsters.at(i).name
				<< "\nHealth: <DEAD>"
				<< "\nStrength: " << monsters.at(i).strength 
				<< "\n" << std::endl;
		}
			
	}
	
	std::cout << "Chose an action by typing it's associated number: " << "\n"
		<< "\t1. Attack" << "\n"
		<< "\t2. Heal" << "\n"
		<< std::endl;
}

void playerAttack(Object& player, Object& monster, std::mt19937& mt)
{
	
	monster.health = defend(monster, attack(player, mt));
	
}

void monsterAttack(Object& player, Object& monster, std::mt19937& mt)
{
	player.health = defend(player, attack(monster, mt));
}

int attack(Object& attacker, std::mt19937& mt)
{
	double strength{ double(attacker.strength) };
	std::normal_distribution d(strength, 2.0);

	int damage{ int(d(mt)) };
	
	return damage;
}

int defend(Object& defender, int damage)
{
	defender.health -= damage;
	std::cout << defender.name << " has taken " << damage << " damage.\n" << std::endl;

	if (defender.health <= 0)
	{
		defender.dead = 1;
	}

	return defender.health;
}

int heal(Object& creature, std::mt19937& mt)
{
	double strength{ double(creature.strength) };
	std::normal_distribution d(strength * 2, 3.0);

	int heal{ int(d(mt)) };
	creature.health += heal;
	std::cout << creature.name << " has healed for " << heal << " health.\n" << std::endl;
	return creature.health;
}
