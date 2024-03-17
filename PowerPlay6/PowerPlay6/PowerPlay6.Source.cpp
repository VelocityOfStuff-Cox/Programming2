#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>
#include "Object.h"
#include "Player.h"

std::random_device seed;
std::default_random_engine engine(seed());

int main()
{
	Player player{ Object::Type::player, 0,1,0, {},0 };
	std::vector<Object> monsters;
	while (player.getHealth(player)  > 0)
	{
		player.levelUp(player);
		monsters  = Object::createMonsters(player);

		std::cout  << monsters.size() << " monster(s) approaches!!" << std::endl;
		system("pause");
		system("cls");

		while (player.getHealth(player)  > 0 && monsters.size() > 0)
		{

			Object::displayBattle(player, monsters);

			std::cout  << "What do you do? (a)ttack (h)eal ";
			char command{ 'x' };
			std::cin  >> command;
			switch (command)
			{
				case 'a':
				{
					Object::playerAttack(player, monsters);
					break;
				}
				case 'h' :
					player.heal(player);
				break;
			default:
				std::cout  << "please enter a or h" << std::endl;
				break;
			}

			Object::bringOutYourDead(monsters);

			Object::monsterAttack(player, monsters);

			system("PAUSE");
			system("CLS");
		}
	}

	if (player.getHealth(player)  <= 0)
	{
		std::cout  << "You Have Died" << std::endl;
	}
	if (player.getHealth(player) <= 0 && monsters.size() == 0)
	{
		std::cout  << "BUT" << std::endl;
	}
	if (monsters.size() == 0)
	{
		std::cout  << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}
