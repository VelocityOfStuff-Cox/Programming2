/*
* Developer: Isabella Cox
* Contact: velocityofstuff1@gmail.com
* Version: 1.0
* Creation Date: 1/20/2024
* Version Creation Date: 1/20/2024
* Written with Visual Studio, assistance from learncpp.com, and cplusspluss.com for function syntax
* ChatGPT 3.5 lightly used to detect complex syntax errors (mostly spelling and hard to see argument closers)
*/

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <array>

struct Entity
{
	std::string name;
	int strength{ 0 };
	int health{ 0 };
};

struct Defeated
{
	std::string name;
	int strength{ 0 };
	std::string status{ "<DEAD>" };
};

int main()
{
	//Mersenne twister set up for uncertain values
	std::mt19937 mt{ std::random_device{}() };
	std::normal_distribution nd{ 5.0, 1.0 };
	std::normal_distribution hnd{ 30.0, 5.0 };
	std::uniform_int_distribution ud{ 1, 3 };

	//Player Character with random strength and health values
	std::string playerName{ "Gongalor" };
	Entity player{ playerName, int(nd(mt)), int(hnd(mt)) };
	//health cap

	//creates one to three entites called "monsters" for the player to fight
	int spawn{ ud(mt) };
	std::vector<Entity> monsters;
	for (int i{ 0 }; i < spawn; i++)
	{
		//intitializes the monster for the current itteration of the loop
		//strength and health are random like the player
		std::string monsterName{ "Monster " + std::to_string(i + 1) };
		monsters.push_back(Entity());
		monsters.back().name = monsterName;
		monsters.back().strength = int(nd(mt));
		monsters.back().health = int(hnd(mt));
	}

	std::cout << "Fight the Monsters" << "\n" << std::endl;

	while (player.health > 0 && monsters.size() > 0)
	{
		std::cout << player.name << ":: Health: " << player.health << ":: Strength: " << player.strength << std::endl;

		for (int i{ 0 }; i < monsters.size(); i++)
		{
			std::cout << i + 1  << ". " << monsters[i].name << ":: Health: " << monsters[i].health << ":: Strength: " << monsters[i].strength << std::endl;
		}

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
				monsters[userInput - 1].health -= player.strength;
				std::cout << "You have attacked for " << player.strength << " damage." << std::endl;
				break;
			}
			else
			{
				std::cout << "Please select a valid target" << std::endl;
				break;
			}
		case 2:
				player.health += player.strength * 2;
				std::cout << "You have healed for " << player.strength * 2 << " health." << std::endl;
				break;
		default:
			std::cout << "Please input an appropriate value." << std::endl;
			break;
		}
		
		std::vector<Defeated> dead;
		for (int i{ 0 }; i < monsters.size(); i++)
		{
			if (monsters[i].health < 0)
			{
				dead.push_back(Defeated());
				dead.back().name = monsters[i].name;
				dead.back().strength = monsters[i].strength;
				monsters.erase(monsters.begin() + i);
			}
		}

		for (int i{ 0 }; i <monsters.size(); i++)
		{
			std::bernoulli_distribution chance(0.75);
			bool attack{ chance(mt) };
			if ( attack == 1)
			{
				std::cout << "You have been attacked for " << monsters[i].strength << " damage." << std::endl;
				player.health -= monsters[i].strength;
			}
			else
			{
				std::cout << "The enemy has healed for " << monsters[i].strength * 2 << " health." << std::endl;
				monsters[i].health += monsters[i].strength * 2;
			}
		}
	}

	if (player.health < 0 && monsters.size() == 0)
	{
		std::cout << "You and the monsters defeated eachother :l Thank you for playing!" << std::endl;
	}
	else if (monsters.size() == 0)
	{
		std::cout << "You defeated the monsters! Thank you for playing!" << std::endl;
	}
	else if (player.health < 0)
	{
		std::cout << "You fell to the monsters :( Thank you for playing!" << std::endl;
	}
	else
	{
		std::cout << "Unknown case. please contact Developer with details. velocityofstuff1@gmail.com" << std::endl;
	}

	int end{};
	std::cin >> end;
	return end;
}