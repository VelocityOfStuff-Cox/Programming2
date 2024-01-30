/*
* Developer: Isabella Cox
* Contact: velocityofstuff1@gmail.com
* Version: 1.1
* Creation Date: 1/20/2024
* Version Creation Date: 1/25/2024
* Written with Visual Studio, assistance from learncpp.com, and cplusspluss.com for function syntax
*/

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

struct Entity
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
	std::string status{ "<ALIVE>" };
};

void displayBattle(Entity player, std::vector<Entity> monsters, std::mt19937 mt);
void playerAttack(Entity player, std::vector<Entity> monsters, std::mt19937 mt);
void monsterAttack(Entity player, std::vector<Entity> monsters, std::mt19937 mt);
int attack(Entity attacker, std::mt19937 mt);
int defend(Entity defender, int damage);
int heal(Entity creature, std::mt19937 mt);

int main()
{
	//Mersenne twister set up for uncertain values
	std::mt19937 mt{ std::random_device{}() };
	std::normal_distribution randStr{ 5.0, 1.0 };
	std::normal_distribution randHp{ 30.0, 5.0 };

	//Player Character with random strength and health values
	Entity player{};
	player.name = "Gongalor";
	player.strength = std::max(1, int(randStr(mt)));
	player.health = std::max(1, int(randHp(mt)));

	//creates one to three entites called "monsters" for the player to fight
	std::uniform_int_distribution ud{ 1, 3 };
	int spawn{ ud(mt) };
	std::vector<Entity> monsters;
	for (int i{ 0 }; i < spawn; i++)
	{
		//intitializes the monster for the current itteration of the loop
		//strength and health are random like the player
		std::string monsterName{ "Monster " + std::to_string(i + 1) };
		monsters.push_back(Entity());
		monsters.back().name = monsterName;
		monsters.back().strength = std::max(1, int(randStr(mt)));;
		monsters.back().health = std::max(1, int(randHp(mt)));
	}

	std::cout << "Fight the Monsters" << "\n" << std::endl;

	while (player.health > 0 && monsters.size() > 0)
	{
		displayBattle(player, monsters, mt);
	}

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

void displayBattle(Entity player, std::vector<Entity> monsters, std::mt19937 mt)
{
	std::cout << player.name
		<< "\nHealth: " << player.health
		<< "\nStrength: " << player.strength 
		<< "\n" << std::endl;

	for (int i{ 0 }; i < monsters.size(); i++)
	{
		if (monsters[i].health > 0)
		{
			std::cout << i + 1 << ". " << monsters[i].name
				<< "\nHealth: " << monsters[i].health
				<< "\nStrength: " << monsters[i].strength 
				<< "\n" << std::endl;
		}
		else
		{
		std::cout << i + 1 << ". " << monsters[i].name
			<< "\nHealth: " << monsters[i].status
			<< "\nStrength: " << monsters[i].strength 
			<< "\n" << std::endl;
		}
			
	}

	playerAttack(player, monsters, mt);
	
	monsterAttack(player, monsters, mt);
}

void playerAttack(Entity player, std::vector<Entity> monsters, std::mt19937 mt)
{
	std::cout << "Chose an action by typing it's associated number: " << "\n"
		<< "\t1. Attack" << "\n"
		<< "\t2. Heal" << "\n"
		<< std::endl;

	int userInput{ 0 };
	std::cin >> userInput;

	switch (userInput)
	{
	case 1:

		std::cout << "Enter the number of the monster you wish to attack" << std::endl;

		std::cin >> userInput;

		if (userInput > 0 && userInput <= monsters.size())
		{
			//the casting syntax was a suggested correection by viual studio
			monsters[static_cast<std::vector<Entity, std::allocator<Entity>>::size_type>(userInput) - 1].health = defend(monsters[userInput - 1], attack(player, mt));
		}
		else
		{
			std::cout << "Please select a valid target" << std::endl;
		}
		break;
	case 2:
		player.health = heal(player, mt);
		break;
	default:
		std::cout << "Please input an appropriate value." << std::endl;
		break;
	}
}

void monsterAttack(Entity player, std::vector<Entity> monsters, std::mt19937 mt)
{
	for (int i{ 0 }; i < monsters.size(); i++)
	{
		std::bernoulli_distribution chance(0.75);
		bool attackHeal{ chance(mt) };
		if (attackHeal == 1)
		{
			player.health = defend(player, attack(monsters[i], mt));
		}
		else
		{
			monsters[i].health = heal(monsters[i], mt);
		}
	}
}

int attack(Entity attacker, std::mt19937 mt)
{
	double strength{ double(attacker.strength) };
	std::normal_distribution d(strength, 2.0);

	int damage{ int(d(mt)) };
	
	return damage;
}

int defend(Entity defender, int damage)
{
	defender.health -= damage;
	std::cout << defender.name << " has taken " << damage << " damage.\n" << std::endl;
	std::cout << defender.health << std::endl;

	if (defender.health <= 0)
	{
		defender.status = "<DEAD>";
	}

	return defender.health;
}

int heal(Entity creature, std::mt19937 mt)
{
	double strength{ double(creature.strength) };
	std::normal_distribution d(strength * 2, 3.0);

	int heal{ int(d(mt)) };
	creature.health += heal;
	std::cout << creature.name << " has healed for " << heal << " health.\n" << std::endl;
	return creature.health;
}
