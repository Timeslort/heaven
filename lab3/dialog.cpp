#include <iostream>
#include "LogicalElement.h"

int GetInt(int&);

int main()
{	
	Prog3::LogicalElement logicElement(15, 1);
	int choice = 1, index;
	short int i;
	const char* dialog[] = {"1.Redefinition", "2.Print all Klemm", "3.Set new Klemm values with preassigned index", 
							"4.Explain Klemm values with preassigned index", "5.Increase connection of Klemm", 
							"6.Decrease connection of Klemm","7.Add new Klemm", "0.Quit"};
	const char* errors[] = { "Invalid value ,try again", "Why?", "You know it's never over",
							"Sry computer will win anyway", "Relax", "Chill man","You scared me"};

	while (choice) {
		std::cout << "Enter number of action :" << std::endl;
		for (i = 0; i < 8; i++)
			std::cout << dialog[i] << std::endl;
		while (GetInt(choice))
			std::cout << errors[rand()%6] << std::endl;
		if (choice > 7 || choice < 0)
			std::cout << "No action with, your number " << std::endl;
		switch (choice) {
		case 1:
			try {
				logicElement.Redefinition();
			}
			catch (std::exception &ex){
				std::cout << ex.what() << std::endl;
			}
			break;
		case 2:
			try {
				logicElement.GetAllKlemm();
			}
			catch (std::exception &ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 3:
			std::cout << "Enter index of Klemm to set : " << std::endl;
			if (GetInt(index))
				std::cout << "What are u typing?" << std::endl;
			try {
				logicElement.SetKlemm(index);
			}
			catch (std::exception &ex){
				std::cout << ex.what() << std::endl;
			}
			break;
		case 4:
			std::cout << "Enter index of Klemm to explain it : " << std::endl;
			if (GetInt(index))
				std::cout << "Nice try." << std::endl;
			try {
				logicElement.GetKlemm(index);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 5:
			std::cout << "Enter index of Klemm to increase connection : " << std::endl;
			if (GetInt(index))
				std::cout << "Ops..." << std::endl;
			try {
				logicElement.IncreaseConnection(index);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 6:
			std::cout << "Enter index of Klemm to increase connection : " << std::endl;
			if (GetInt(index))
				std::cout << "Not today." << std::endl;
			try {
				logicElement.IncreaseConnection(index);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 7:
			try {
				logicElement.AddKlemm();
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		}
	}

	return 0;
}

int GetInt(int &a) {
	std::cin >> a;
	if (!std::cin.good()) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		return Prog3::INVALID_VALUE;
	}
	return Prog3::SUCCESS;
}