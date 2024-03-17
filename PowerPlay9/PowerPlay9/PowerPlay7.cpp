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
void bringOutYourDead(std::vector<Monster>& monsters);


int main()
{
	std::vector<Object*> objects;
	Player* player{ objects.at(0) };
	while (!player->isDead())
	{
		player->levelUp();
		objects = createMonsters(*player);

		std::cout << objects.size() - 1 << " monster(s) approaches!!" << std::endl;
		system("pause");

		while (!player->isDead() && objects.size() - 1 > 0)
		system("cls");
		{
			displayBattle(*player, objects);

			player->update(*player, objects);

			bringOutYourDead(objects);

			std::cout << std::endl;
			std::for_each(objects.begin(), objects.end(), [&](Monster& monster)
				{
					monster.update(*player, objects);
				});

			system("PAUSE");
			system("CLS");
		}
	}

	if (player->isDead())
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (player->isDead() && objects.size() - 1 == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (objects.size() - 1 == 0)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}



void displayBattle(const Player& player, const std::vector<Monster>& monsters)
{
	Object::nameOnly = false; //TODO:: get rid of this and just dot he full cout.
	std::cout << player << std::endl;
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
	std::vector<Object*> monsters(std::max(1, (int)randomNumMonsters(Object::engine)));
	std::generate(monsters.begin(), monsters.end(), [&]()
		{
			return Monster(player);
		});
	return monsters;
}

void bringOutYourDead(std::vector<Monster>& monsters)
{
	Object::nameOnly = true;
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
