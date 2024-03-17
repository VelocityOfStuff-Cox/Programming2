#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

std::vector<Monster> createMonsters(const Player& player);

void displayBattle(const Player& player, const std::vector<Monster>& monsters);
void playerAttack(const Player& player, std::vector<Monster>& monsters);
void monsterAttack(Player& player, const std::vector<Monster>& monsters);
void bringOutYourDead(std::vector<Monster>& monsters);


int main()
{
	Player player;
	std::vector<Monster> monsters;
	while (!player.isDead())
	{
		player.levelUp();
		monsters = createMonsters(player);

		std::cout << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (!player.isDead() && monsters.size() > 0)
		{

			displayBattle(player, monsters);

			std::cout << "What do you do? (a)ttack (h)eal ";
			char command{ 'x' };
			std::cin >> command;
			switch (command)
			{
			case 'a':
			{
				playerAttack(player, monsters);
				break;
			}
			case 'h':
				player.heal();
				break;
			default:
				std::cout << "please enter a or h" << std::endl;
				break;
			}

			bringOutYourDead(monsters);

			monsterAttack(player, monsters);

			system("PAUSE");
			system("CLS");
		}
	}

	if (player.isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player.isDead() && monsters.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(const Player& player, const std::vector<Monster>& monsters)
{
	std::cout << player << std::endl;
	std::cout << player.getInventory();


	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(monsters.begin(), monsters.end(), [&](const Monster& monster)
			{
				std::cout << "   " << i << ". " << monster << std::endl;

				i++;
			});
	}
}

std::vector<Monster> createMonsters(const Player& player)
{
	std::normal_distribution<double> randomNumMonsters((double)player.getLevel(), player.getLevel() / 2.0);
	std::vector<Monster> monsters(std::max(1, (int)randomNumMonsters(Object::engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			return Monster(player);
		});
	return monsters;
}

void monsterAttack(Player& player, const std::vector<Monster>& monsters)
{

	std::cout << std::endl;
	std::for_each(monsters.begin(), monsters.end(), [&](const Monster& monster)
		{
			
			std::bernoulli_distribution willAttack(.75);
			if (willAttack(Object::engine))
			{

				std::cout << monster << " attacks!" << std::endl;
				player.defense(monster.damage());
			}
			else
			{

				std::cout << monster << " twiddles its thumbs" << std::endl;
			}
		});
}

void playerAttack(const Player& player, std::vector<Monster>& monsters)
{
	std::cout << "Which Monster: ";
	int monsterNum{ 0 };
	std::cin >> monsterNum;
	if (monsterNum > 0 && monsterNum <= monsters.size())
	{

		monsters[monsterNum - 1].defense(player.damage());
	}
}


void bringOutYourDead(std::vector<Monster>& monsters)
{
	monsters.erase(
		std::remove_if(monsters.begin(), monsters.end(),
			[](Object& monster)
			{
				if (monster.isDead())
				{

					std::cout << monster << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		monsters.end());

}
