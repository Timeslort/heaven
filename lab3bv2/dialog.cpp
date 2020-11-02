#include<iostream>
#include"LogicElement.h"
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>

int main() {
	//_CrtSetBreakAlloc(187);
	Prog3::LogicElement logicElement(3, 1);
	Prog3::LogicElement copyLogicElement(logicElement);
	Prog3::LogicElement eqvlLogicElement;
	std::cout << logicElement;
	std::cout << copyLogicElement;
	std::cout << eqvlLogicElement;
	eqvlLogicElement = logicElement;
	
	Prog3::LogicElement::Iterator itr;

	int num = 1;
	for (itr = logicElement.begin(); itr != logicElement.end(); ++itr, num++) {
		LINE;
		std::cout << "Klemm #" << num << std::endl
			<< (*itr) << std::endl;
		LINE;
	}

	
	std::cout << eqvlLogicElement;
	Prog3::Klemm test;
	int number, nConn, index, choice = 1;
	char nSig;
	int i;
	char typeName[10];
	const char* dialog[] = { "1.Redefinition", "2.Print all Klemm", "3.Set new Klemm values with preassigned number",
							"4.Explain Klemm values with preassigned index", "5.Increase connection of Klemm",
							"6.Decrease connection of Klemm","7.Add new Klemm", "0.Quit" };
	const char* errors[] = { "Invalid value ,try again", "Why?", "You know it's never over",
							"Sry computer will win anyway", "Relax", "Chill man","You scared me" };

	while (choice) {
		std::cout << "Enter number of action :" << std::endl;
		for (i = 0; i < 8; i++)
			std::cout << dialog[i] << std::endl;
		while (Prog3::GetInt(choice))
			std::cout << errors[rand() % 6] << std::endl;
		if (choice > 7 || choice < 0)
			std::cout << "No action with, your number " << std::endl;
		switch (choice) {
		case 1:
			std::cin >> logicElement;
			break;
		case 2:
			std::cout << logicElement;
			break;
		case 3:
			std::cout << "Enter number of Klemm to set : " << std::endl;
			if (Prog3::GetInt(number)) {
				std::cout << "What are u typing?" << std::endl;
				break;
			}
			std::cout << "Enter type of Klemm to set (Entrance, Output): " << std::endl;
			std::cin >> typeName;
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Enter number of Klemm connection to set : " << std::endl;
			if (Prog3::GetInt(nConn)) {
				std::cout << "What are u typing?" << std::endl;
				break;
			}
			std::cout << "Enter signal state of Klemm to set(0, 1, X) : " << std::endl;
			std::cin >> nSig;
			std::cin.clear();
			while (std::cin.get() != '\n');
			try {
				logicElement(number, typeName, nConn, nSig);
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		case 4:
			std::cout << "Enter index of Klemm to explain it : " << std::endl;
			if (Prog3::GetInt(index)) {
				std::cout << "Nice try." << std::endl;
				break;
			}
			if (index > (logicElement.getSize() - 1) || index < 0) {
				std::cout << "You type wrong index!";
				break;
			}
			std::cout << logicElement[index];
			break;
		case 5:
			std::cout << "Enter index of Klemm to increase connection : " << std::endl;
			if (Prog3::GetInt(index)) {
				std::cout << "Ops..." << std::endl;
				break;
			}
			std::cout << "Element have value :" << logicElement[index].getConnection() << std::endl;
			/*if (logicElement[index].type == Prog3::ENTRANCE && logicElement[index].connection == 1) {
				std::cout << ("You can't change number of connection, because its max!!!");
				break;
			}
			if (logicElement[index].type == Prog3::OUTPUT && logicElement[index].connection == 3) {
				std::cout << ("You can't change number of connection, because its max!!!");
				break;
			}*/
			try {
				++logicElement[index];
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			std::cout << "New number of connection is " << logicElement[index].getConnection() << std::endl;
			break;
		case 6:
			std::cout << "Enter index of Klemm to decrease connection : " << std::endl;
			if (Prog3::GetInt(index)) {
				std::cout << "Not today." << std::endl;
				break;
			}
			std::cout << "Element have value :" << logicElement[index].getConnection() << std::endl;
			/*if (logicElement[index].connection == 0) {
				std::cout << ("You can't change number of connection, because its minimum!!!");
				break;
			}*/
			try {
				--logicElement[index];
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			std::cout << "New number of connection is " << logicElement[index].getConnection() << std::endl;
			break;
		case 7:
			std::cout << "Enter type of Klemm to add (Entrance, Output): " << std::endl;
			std::cin >> typeName;
			std::cin.clear();
			while (std::cin.get() != '\n');
			try {
				logicElement += typeName;
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			break;
		}
	}
	_CrtDumpMemoryLeaks();
	return 0;
}