#include<iostream>
#include<exception>
#include"LogicalElement.h"
#include<time.h>
#include<stdlib.h>
#define LINE std::cout << "|-------------------------------------|" << std::endl

namespace Prog3 {

	LogicalElement::LogicalElement(int in, int out) {
		if (in < 0 || in > 20)
			throw std::invalid_argument("Invalid argument, number of entence klemm set in 0");
		numEntence = in;
		if (in < 0 || in + out > 20)
			throw std::invalid_argument("Invalid argument, number of outout klemm set in 0");
		numOutput = out;
		for (register short i = 0; i < in; i++) {
			array[i].connection = 1;
			array[i].type = ENTRANCE;
		}
		srand(time(NULL));
		for (register short i = in; i < out + in; i++) {
			array[i].connection = rand() % 4;
			array[i].type = OUTPUT;
		}
	}

	LogicalElement::LogicalElement(Klemm &klemm, int count) {
		if (count <= 0 || count > 20)
			throw std::invalid_argument("Invalid argument,count cant be lower then 1");
		if (klemm.type == ENTRANCE)
			if (klemm.connection > 1 || klemm.connection < 0)
				throw std::invalid_argument("Invalid argument,connection of entance item cant take this value!");
		if (klemm.type == OUTPUT)
			if (klemm.connection > 3 || klemm.connection < 0)
				throw std::invalid_argument("Invalid argument,connection of output item cant take this value!");

		for (register short i = 0; i < count; i++) {
			array[i].connection = klemm.connection;
			array[i].type = klemm.type;
			array[i].signal = klemm.signal;
		}
	}

	void LogicalElement::GetKlemm(void) {

		if (numEntence == 0 && numOutput == 0)
			throw std::invalid_argument("Array of Klemm is empry!");

		int number;
		std::cout << "Enter Klemm number :" << std::endl;
		if (CurrectChoice(number, 1, 20)) {
			throw std::invalid_argument("Incorrect number!!!");
		}
		if (number > numEntence + numOutput)
			throw std::invalid_argument("Incorrect index, cant find");
		std::cout << "Klemm found :" << std::endl
			<< "Type is : ";
		if (array[number - 1].type == OUTPUT)
			std::cout << "Output" << std::endl;
		else
			std::cout << "Entrance" << std::endl;
		std::cout << "Numer of connection : " << array[number - 1].connection << std::endl
			<< "Signal state is : ";
		if (array[number - 1].signal == 3)
			std::cout << "X" << std::endl;
		else
			std::cout << array[number - 1].type << std::endl;
	}

	void LogicalElement::GetKlemm(int index) const {

		if (numEntence == 0 && numOutput == 0)
			throw std::invalid_argument("Array of Klemm is empry!");

		if (index + 1 > numEntence + numOutput)      //?
			throw std::invalid_argument("Incorrect index, cant find");
		LINE;
		std::cout << "Type is : ";
		if (array[index].type == OUTPUT)
			std::cout << "Output" << std::endl;
		else
			std::cout << "Entrance" << std::endl;
		std::cout << "Numer of connection : " << array[index].connection << std::endl
			<< "Signal state is : ";
		if (array[index].signal == 3)
			std::cout << "X" << std::endl;
		else
			std::cout << array[index].type << std::endl;
		LINE;
	}

	void LogicalElement::Redefinition(void) {
		int choice, newType, newConnection, newSignal, countOut = 0, countEnt = 0;
		register short int i;

		std::cout << "Pls enter number of action :" << std::endl
			<< "1.Redefenition all Klemm." << std::endl
			<< "2.Redefenition only entrance Klemm." << std::endl
			<< "3.Redefenition only output Klemm." << std::endl;
		if (CurrectChoice(choice, 1, 3))
			throw std::invalid_argument("Inccorect input!!!");
		switch (choice) {
		case 1:
			for (i = 0; i < numEntence + numOutput; i++) {
				std::cout << i + 1 << ".Klemm have values :" << std::endl;
				GetKlemm(i);
				std::cout << "Enter number of new type : " << std::endl
					<< "1.Entence" << std::endl
					<< "2.Output" << std::endl
					<< "Or u can quit if press 3" << std::endl;
				while (CurrectChoice(choice, 1, 3)) {
					std::cout << "Incorrect value!!! Try again!" << std::endl;
				}
				if (choice == 3)
					break;
				if (choice == ENTRANCE)
					newType = ENTRANCE;
				else
					newType = OUTPUT;
				std::cout << "Enter number of new connection : " << std::endl;
				if (newType == ENTRANCE)
					while (CurrectChoice(newConnection, 0, 1))
						std::cout << "Incorrect value (Entence Klemm can have from zero to one connections!!!).Try again!" << std::endl;
				else
					while (CurrectChoice(newConnection, 0, 3))
						std::cout << "Incorrect value (Output Klemm can have from zero to three connections!!!).Try again!" << std::endl;
				std::cout << "Enter number of new signal state (0, 1, X): " << std::endl;
				while (GetSignal(newSignal))
					std::cout << "Incorrect value !!!" << std::endl;
				array[i].type = newType;
				array[i].connection = newConnection;
				array[i].signal = newSignal;
				std::cout << "New Klemm is : " << std::endl;
				GetKlemm(i);
			}
			break;
		case 2:
			for (i = 0; i < numEntence + numOutput; i++) {
				if (array[i].type == ENTRANCE) {
					countEnt++;
					std::cout << i + 1 << ".Klemm have values :" << std::endl;
					GetKlemm(i);
					std::cout << "Enter number of new type : " << std::endl
						<< "1.Entence" << std::endl
						<< "2.Output" << std::endl
						<< "Or u can quit if press 3" << std::endl;
					while (CurrectChoice(choice, 1, 3)) {
						std::cout << "Incorrect value!!! Try again!" << std::endl;
					}
					if (choice == 3)
						break;
					if (choice == ENTRANCE)
						newType = ENTRANCE;
					else
						newType = OUTPUT;
					std::cout << "Enter number of new connection : " << std::endl;
					if (newType == ENTRANCE)
						while (CurrectChoice(newConnection, 0, 1))
							std::cout << "Incorrect value (Entence Klemm can have from zero to one connections!!!).Try again!" << std::endl;
					else
						while (CurrectChoice(newConnection, 0, 3))
							std::cout << "Incorrect value (Output Klemm can have from zero to three connections!!!).Try again!" << std::endl;
					std::cout << "Enter number of new signal state (0, 1, X): " << std::endl;
					while (GetSignal(newSignal))
						std::cout << "Incorrect value !!!" << std::endl;
					array[i].type = newType;
					array[i].connection = newConnection;
					array[i].signal = newSignal;
					std::cout << "New Klemm is : " << std::endl;
					GetKlemm(i);
					if (countEnt == numEntence)
						break;
				}
			}
				break;
		case 3:
			for (i = 0; i < numEntence + numOutput; i++) {
				if (array[i].type == OUTPUT) {
					countOut++;
					std::cout << i + 1 << ".Klemm have values :" << std::endl;
					GetKlemm(i);
					std::cout << "Enter number of new type : " << std::endl
						<< "1.Entence" << std::endl
						<< "2.Output" << std::endl
						<< "Or u can quit if press 3" << std::endl;
					while (CurrectChoice(choice, 1, 3)) {
						std::cout << "Incorrect value!!! Try again!" << std::endl;
					}
					if (choice == 3)
						break;
					if (choice == ENTRANCE)
						newType = ENTRANCE;
					else
						newType = OUTPUT;
					std::cout << "Enter number of new connection : " << std::endl;
					if (newType == ENTRANCE)
						while (CurrectChoice(newConnection, 0, 1))
							std::cout << "Incorrect value (Entence Klemm can have from zero to one connections!!!).Try again!" << std::endl;
					else
						while (CurrectChoice(newConnection, 0, 3))
							std::cout << "Incorrect value (Output Klemm can have from zero to three connections!!!).Try again!" << std::endl;
					std::cout << "Enter number of new signal state (0, 1, X): " << std::endl;
					while (GetSignal(newSignal))
						std::cout << "Incorrect value !!!" << std::endl;
					array[i].type = newType;
					array[i].connection = newConnection;
					array[i].signal = newSignal;
					std::cout << "New Klemm is : " << std::endl;
					GetKlemm(i);
					if (countOut == numOutput)
						break;
				}
			}
				break;
		}

	}

	void LogicalElement::SetKlemm(int index) {
		if (index + 1 > numEntence + numOutput || index < 0)
			throw std::invalid_argument("Incorrect index!!!");

		int choice, newType, newConnection, newSignal;
		std::cout << "Klemm have values :" << std::endl;
		GetKlemm(index);
		std::cout << "Enter number of new type : " << std::endl
			<< "1.Entence" << std::endl
			<< "2.Output" << std::endl;
		while (CurrectChoice(choice, 1, 2)) {
			std::cout << "Incorrect value!!! Try again!" << std::endl;
		}
		if (choice == ENTRANCE)
			newType = ENTRANCE;
		else
			newType = OUTPUT;
		std::cout << "Enter number of new connection : " << std::endl;
		if (newType == ENTRANCE)
			while (CurrectChoice(newConnection, 0, 1))
				std::cout << "Incorrect value (Entence Klemm can have from zero to one connections!!!).Try again!" << std::endl;
		else
			while (CurrectChoice(newConnection, 0, 3))
				std::cout << "Incorrect value (Output Klemm can have from zero to three connections!!!).Try again!" << std::endl;
		std::cout << "Enter number of new signal state (0, 1, X): " << std::endl;
		while (GetSignal(newSignal))
			std::cout << "Incorrect value !!!" << std::endl;
		array[index].type = newType;
		array[index].connection = newConnection;
		array[index].signal = newSignal;
		std::cout << "New Klemm is : " << std::endl;
		GetKlemm(index);
	}

	void LogicalElement::GetAllKlemm(void) const {
		std::cout << "Number of all Klemm " << numEntence + numOutput << std::endl
			<< "Number of Entence Klemm " << numEntence << std::endl
			<< "Number of Output Klemm" << numOutput << std::endl
			<< "List of all Klemm :" << std::endl;
		if (numEntence + numOutput == 0)
			std::cout << "Is Empty." << std::endl;
		for (short i = 0; i < numEntence + numOutput; i++)
			GetKlemm(i);
	}

	void LogicalElement::AddKlemm(void) {
		if (numEntence + numOutput >= 20)
			throw std::invalid_argument("Array of Klamm's is overflow");

		int choice, newType, newConnection, newSignal;
		std::cout << "Enter number of new type : " << std::endl
			<< "1.Entence" << std::endl
			<< "2.Output" << std::endl;
		while (CurrectChoice(choice, 1, 2)) {
			std::cout << "Incorrect value!!! Try again!" << std::endl;
		}
		if (choice == ENTRANCE)
			newType = ENTRANCE;
		else
			newType = OUTPUT;
		std::cout << "Enter number of new connection : " << std::endl;
		if (newType == ENTRANCE)
			while (CurrectChoice(newConnection, 0, 1))
				std::cout << "Incorrect value (Entence Klemm can have from zero to one connections!!!).Try again!" << std::endl;
		else
			while (CurrectChoice(newConnection, 0, 3))
				std::cout << "Incorrect value (Output Klemm can have from zero to three connections!!!).Try again!" << std::endl;
		std::cout << "Enter number of new signal state (0, 1, X): " << std::endl;
		while (GetSignal(newSignal))
			std::cout << "Incorrect value !!!" << std::endl;
		int wIndex = numEntence + numOutput;
		array[wIndex].type = newType;
		array[wIndex].connection = newConnection;
		array[wIndex].signal = newSignal;
		std::cout << "Adding Klemm is : " << std::endl;
		GetKlemm(wIndex);
		if (newType == ENTRANCE)
			numEntence++;
		else
			numOutput++;
	}
	void LogicalElement::IncreaseConnection(int index) {
		if (index + 1 > numEntence + numOutput || index < 0)
			throw std::invalid_argument("Incorrect index!!!");

		int value;
		std::cout << "Element with index " << index << " have values :" << array[index].connection << std::endl;
		if (array[index].type == ENTRANCE)
			if (array[index].connection == 1)
				throw std::invalid_argument("You can't change number of connection, because its max!!!");
		if (array[index].type != ENTRANCE)
			if (array[index].connection == 3)
				throw std::invalid_argument("You can't change number of connection, because its max!!!");
		std::cout << "How much do you want to increase the value of connection?" << std::endl;
		if (array[index].type == ENTRANCE)
			while (CurrectChoice(value, array[index].connection, 1))
				std::cout << "It's too big value! Entrace Klemm can have only zero or one connection." << std::endl
				<< "Now value of connection is 0" << std::endl;
		else 
			while (CurrectChoice(value, array[index].connection, 3))
				std::cout << "It's too big value! Output Klemm can have only from zero to three connection." << std::endl
				<< "Now value of connection is " << array[index].connection << std::endl;
		array[index].connection += value;
		std::cout << "New number of connection is " << array[index].connection << std::endl;
	}

	void LogicalElement::DecreaseConnection(int index) {
		if (index + 1 > numEntence + numOutput || index < 0)
			throw std::invalid_argument("Incorrect index!!!");

		int value;
		std::cout << "Element with index " << index << " have values :" << array[index].connection << std::endl;
		
		if (array[index].connection == 0)
			throw std::invalid_argument("You can't change number of connection, because its minimum!!!");
		
		std::cout << "How much do you want to decrease the value of connection?" << std::endl;
		if (array[index].type == ENTRANCE)
			while (CurrectChoice(value, array[index].connection, 1))
				std::cout << "It's too big value! Entrace Klemm can have only zero or one connection." << std::endl
				<< "Now value of connection is 1!" << std::endl;
		else
			while (CurrectChoice(value, 0, array[index].connection))
				std::cout << "It's too big value! Output Klemm can have only from zero to three connection." << std::endl
				<< "Now value of connection is " << array[index].connection << std::endl;
		array[index].connection -= value;
		std::cout << "New number of connection is " << array[index].connection << std::endl;
	}

	Error LogicalElement::GetSignal(int& signal) {
		char in_signal;
		std::cin >> in_signal;
		if (!std::cin.good() || (in_signal != '1' && in_signal != '0' && in_signal != 'X')) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return INVALID_VALUE;
		}
		if (in_signal == '1')
			signal = 1;
		if (in_signal == '0')
			signal = 0;
		if (in_signal == 'X')
			signal = 3;
		return SUCCESS;
	}

	Error LogicalElement::CurrectChoice(int& a, int start, int end) {
		std::cin >> a;
		if (!std::cin.good() || a < start || a > end) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return INVALID_VALUE;
		}
		return SUCCESS;
	}
}