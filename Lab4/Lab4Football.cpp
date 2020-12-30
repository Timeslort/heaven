#include "team.h"

int getint(int&);

int main()
{
    Prog4::Game oftrones;
    Prog4::Team wolfs;
	Prog4::Date index;
	std::cout << "enter information about your team!" << std::endl;
	std::cin >> wolfs;
	int choice = 1;
	int i;
		

	const char* dialog[] = { "1.redefinition", "2.print all games", "3.explain team information",
							"4.explain game with preassigned date", "5.add new game",
							"6.remove game", "0.quit" };
	const char* errors[] = { "invalid value ,try again", "why?", "you know it's never over",
							"sry computer will win anyway", "relax", "chill man","you scared me" };

	while (choice) {
		std::cout << "enter number of action :" << std::endl;
		for (i = 0; i < 7; i++)
			std::cout << dialog[i] << std::endl;
		while (getint(choice))
			std::cout << errors[rand() % 6] << std::endl;
		if (choice > 6 || choice < 0)
			std::cout << "no action with, your number " << std::endl;
		switch (choice) {
		case 1:
			std::cin >> wolfs;
			break;
		case 2:
			wolfs.GetTable();
			break;
		case 3:
			std::cout << wolfs;
			break;
		case 4:
			std::cout << "enter date of game to explain it : " << std::endl;
			std::cin >> index;
			try {
				std::cout << wolfs.FindElement(index);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 5:
			std::cout << "type info about game : " << std::endl;
			std::cin >> oftrones;
			wolfs.AddGame(oftrones);
			break;
		case 6:
			std::cout << "enter date of game to remove it : " << std::endl;
			std::cin >> index;
			try {
				wolfs.RemoveGame(index).GetTable();
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		}
	}

	return 0;
}

int getint(int& a) {
	std::cin >> a;
	if (!std::cin.good()) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		return 1;
	}
	return 0;
}
