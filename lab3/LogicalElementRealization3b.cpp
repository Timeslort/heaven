#include<iostream>
#include<exception>
#include"LogicalElement3b.h"
#include<time.h>
#include<stdlib.h>
#include<string.h>
#define LINE std::cout << "|-------------------------------------|" << std::endl

namespace Prog3 {

	LogicalElement::LogicalElement(int in, int out) {
		if (in < 0)
			throw std::invalid_argument("Invalid argument");
		numEntence = in;
		if (out < 0)
			throw std::invalid_argument("Invalid argument");
		numOutput = out;
		size = numOutput + numEntence;
		try { 
			array = new Klemm[size]; 
		}
		catch (std::bad_alloc &ba) {
			std::cout << ba.what();
			throw std::invalid_argument("Invalid argument");
		}
		
		srand(time(NULL));
		for (register short i = 0; i < in; i++) {
			array[i].connection = rand()%2;
			array[i].type = ENTRANCE;
		}
		for (register short i = in; i < out + in; i++) {
			array[i].connection = rand() % 4;
			array[i].type = OUTPUT;
		}
		size = numEntence + numOutput;
	}

	LogicalElement::LogicalElement(Klemm &klemm, int count) {
		if (count < 0 )
			throw std::invalid_argument("Invalid argument,count cant be lower then 0");
		if (klemm.signal > 3 || klemm.signal < 0 || klemm.signal == 2)
			throw std::invalid_argument("Invalid argument,signal state cant take this value!");
		if (klemm.type == ENTRANCE) {
			if (klemm.connection > 1 || klemm.connection < 0)
				throw std::invalid_argument("Invalid argument,connection of entance item cant take this value!");
			numEntence = count;
			numOutput = 0;
		}
		else if (klemm.type == OUTPUT) {
				if (klemm.connection > 3 || klemm.connection < 0)
					throw std::invalid_argument("Invalid argument,connection of output item cant take this value!");
				numEntence = 0;
				numOutput = count;
		}
		else
			throw std::invalid_argument("Invalid type!");

		size = count;
		try {
			array = new Klemm[size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what();
			throw std::invalid_argument("Invalid argument");
		}

		for (register short i = 0; i < count; i++) {
			array[i].connection = klemm.connection;
			array[i].type = klemm.type;
			array[i].signal = klemm.signal;
		}
	}

	LogicalElement::LogicalElement(LogicalElement &copy) {
		numEntence = copy.numEntence;
		numOutput = copy.numOutput;
		size = copy.size;
		try {
			array = new Klemm[size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what();
			throw std::invalid_argument("Invalid argument");
		}
		for (register short i = 0; i < size; i++) {
			array[i].type = copy.array[i].type;
			array[i].connection = copy.array[i].connection;
			array[i].signal = copy.array[i].signal;
		}
	}

	void LogicalElement::GetKlemm(void) {

		if (numEntence == 0 && numOutput == 0)
			throw std::invalid_argument("Array of Klemm is empry!");

		int number;
		std::cout << "Enter Klemm number :" << std::endl;
		if (CurrectChoice(number, 1, size)) {
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
			std::cout << array[index].signal << std::endl;
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
	//	if (numEntence + numOutput >= 20)
	//		throw std::invalid_argument("Array of Klamm's is overflow");

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
		size = numEntence + numOutput;
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

	std::ostream& operator<<(std::ostream& output, const LogicalElement& outElmnt) {
		if (outElmnt.size == 0)
			output << "Array is empty" << std::endl;
		for (int i = 0; i < outElmnt.size; i++) {
			LINE;
			output << "Klem #" << i + 1 << std::endl;
			output << "Type is : ";
			if (outElmnt.array[i].type == ENTRANCE)
				output << "Entrance" << std::endl;
			else
				output << "Output" << std::endl;
			output << "Number of connection is :" << outElmnt.array[i].connection << std::endl
				<< "Signal state is :";
			if (outElmnt.array[i].signal == 3)
				output << "X" << std::endl;
			else
				output << outElmnt.array[i].signal << std::endl;
		}
		LINE;
		return output; //позволяет cout << a << b << c;
	}

	std::ostream& operator<<(std::ostream &output, const Klemm &wKlm) {
		LINE;
		output << "Type is : ";
		if (wKlm.type == ENTRANCE)
			output << "Entrance" << std::endl;
		else
			output << "Output" << std::endl;
		output << "Number of connection is :" << wKlm.connection << std::endl
			<< "Signal state is :";
		if (wKlm.signal == 3)
			output << "X" << std::endl;
		else
			output << wKlm.signal << std::endl;
		LINE;
		return output;
	}

	std::istream& operator>>(std::istream& input, LogicalElement &inputElmnt) {
		int newConnection;
		char strType[10];
		char newSignal;
		for (int i = 0; i < inputElmnt.size; i++) {
			std::cout << "Enter new type (Entrance, Output) : ";
			input >> strType;
			input.clear();
			while (input.get() != '\n');
			if (!CurrectString("entrance", strType))
				if (inputElmnt.array[i].type != ENTRANCE) {
					inputElmnt.array[i].type = ENTRANCE;
					inputElmnt.numEntence++;
					inputElmnt.numOutput--;
				}
				else;
			else
				if (!CurrectString("output", strType))
					if (inputElmnt.array[i].type != OUTPUT) {
						inputElmnt.array[i].type = OUTPUT;
						inputElmnt.numEntence--;
						inputElmnt.numOutput++;
					}
					else;
				else
					throw std::invalid_argument("Incorrect type");
			
			if (inputElmnt.array[i].type == ENTRANCE)
				std::cout << std::endl << "Enter new number of connection (for entrance type 0,1) : ";
			else 
				std::cout << std::endl << "Enter new number of connection (for output type 0,1,2,3) : ";
			input >> newConnection;
			if (!input.good()) {
				input.clear();
				while (input.get() != '\n');
				throw std::invalid_argument("Incorrect input");
			}
			if (inputElmnt.array[i].type == ENTRANCE)
				if (newConnection > 1 || newConnection < 0)
					throw std::invalid_argument("Incorrect connection number for entrance Klemm");
				else
					inputElmnt.array[i].connection = newConnection;
			else 
				if (newConnection > 3 || newConnection < 0)
					throw std::invalid_argument("Incorrect connection number for Output Klemm");
				else 
					inputElmnt.array[i].connection = newConnection;

			std::cout << std::endl << "Enter new number of signal state(0, 1, X) : ";
			input >> newSignal;
			if (!input.good()) {
				input.clear();
				while (input.get() != '\n');
				throw std::invalid_argument("Incorrect input");
			}
			input.clear();
			while (input.get() != '\n');
			if (newSignal == '1')
				inputElmnt.array[i].signal = 1;
			if (newSignal == '0')
				inputElmnt.array[i].signal = 0;
			if (newSignal == 'X')
				inputElmnt.array[i].signal = 3;
			if (newSignal != 'X' && newSignal != '0' && newSignal != '1')
				throw std::invalid_argument("Incorrect signal");
		}
		return input;
	}

	std::istream& operator>>(std::istream& input, Klemm& inputKlm) { //std::cin >> inputKlm -> operator>>(std::cin, inputKlm);
		int newConnection;
		char strType[10];
		char newSignal;
		std::cout << "Enter new type (Entrance, Output) : ";
		input >> strType;
		input.clear();
		while (input.get() != '\n');
		if (!CurrectString("entrance", strType))
			inputKlm.type = ENTRANCE;
		else
			if (!CurrectString("output", strType))
				inputKlm.type = OUTPUT;
			else
				throw std::invalid_argument("Incorrect type");

		if (inputKlm.type == ENTRANCE)
			std::cout << std::endl << "Enter new number of connection (for entrance type 0,1) : ";
		else
			std::cout << std::endl << "Enter new number of connection (for output type 0,1,2,3) : ";
		input >> newConnection;
		if (!input.good()) {
			input.clear();
			while (input.get() != '\n');
			throw std::invalid_argument("Incorrect input");
		}
		if (inputKlm.type == ENTRANCE)
			if (newConnection > 1 || newConnection < 0)
				throw std::invalid_argument("Incorrect connection number for entrance Klemm");
			else
				inputKlm.connection = newConnection;
		else
			if (newConnection > 3 || newConnection < 0)
				throw std::invalid_argument("Incorrect connection number for Output Klemm");
			else
				inputKlm.connection = newConnection;

		std::cout << std::endl << "Enter new number of signal state(0, 1, X) : ";
		input >> newSignal;
		if (!input.good()) {
			input.clear();
			while (input.get() != '\n');
			throw std::invalid_argument("Incorrect input");
		}
		input.clear();
		while (input.get() != '\n');
		if (newSignal == '1')
			inputKlm.signal = 1;
		if (newSignal == '0')
			inputKlm.signal = 0;
		if (newSignal == 'X')
			inputKlm.signal = 3;
		if (newSignal != 'X' && newSignal != '0' && newSignal != '1')
			throw std::invalid_argument("Incorrect signal");
	}

	Klemm& LogicalElement::operator[](const int index) {
		if (index >= numEntence + numOutput || index < 0)
			throw std::invalid_argument("out of array space!!!");

		return array[index];
	}

	void LogicalElement::operator()(int numOfKlmm, char* wType, int con, char sgnl) {
		int index = numOfKlmm - 1;
		if (index >= numEntence + numOutput || index < 0)
			throw std::invalid_argument("out of array space!!!");

		if (!CurrectString("entrance", wType))
			if (array[index].type != ENTRANCE) {
				array[index].type = ENTRANCE;
				numEntence++;
				numOutput--;
			}
			else;
		else
			if (!CurrectString("output", wType))
				if (array[index].type != OUTPUT) {
					array[index].type = OUTPUT;
					numEntence--;
					numOutput++;
				}
				else;
			else
				throw std::invalid_argument("Incorrect type");

		if (array[index].type == ENTRANCE)
			if (con > 1 || con < 0)
				throw std::invalid_argument("Incorrect connection number for entrance Klemm");
			else
				array[index].connection = con;
		else
			if (con > 3 || con < 0)
				throw std::invalid_argument("Incorrect connection number for Output Klemm");
			else
				array[index].connection = con;

		if (sgnl == '1')
			array[index].signal = 1;
		if (sgnl == '0')
			array[index].signal = 0;
		if (sgnl == 'X')
			array[index].signal = 3;
		if (sgnl != 'X' && sgnl != '0' && sgnl != '1')
			throw std::invalid_argument("Incorrect signal");
		
	}

	void operator+=(LogicalElement &wElement, char* wType){
	//	if (wElement.numEntence + wElement.numOutput == 20)
	//		throw std::invalid_argument("Array overflow");

		if (!CurrectString("entrance", wType)) {
			try {
				wElement.ChangeSpace();
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				throw std::invalid_argument("Dont have enough space!");
			}

			wElement.array[wElement.size - 1].type = ENTRANCE;
			wElement.numEntence++;
		}
		else
			if (!CurrectString("output", wType)) {
				try {
					wElement.ChangeSpace();
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					throw std::invalid_argument("Dont have enough space!");
				}
				wElement.array[wElement.size - 1].type = OUTPUT;
				wElement.numOutput++;
			}
			else
				throw std::invalid_argument("Incorrect type");
	}
	
	void operator+=(LogicalElement &wElement, Klemm &wKlemm) {
	//	if (wElement.numEntence + wElement.numOutput == 20)
	//	throw std::invalid_argument("Array overflow");

		if (wKlemm.signal > 3 || wKlemm.connection < 0)
				throw std::invalid_argument("Invalid signal value");
		if (wKlemm.type == ENTRANCE) {
			if (wKlemm.connection > 1 || wKlemm.connection < 0)
				throw std::invalid_argument("Invalid connection value");
			try {
				wElement.ChangeSpace();
			}
			catch (std::exception& ex) {
				std::cout << ex.what() << std::endl;
				throw std::invalid_argument("Dont have enough space!");
			}
			wElement.array[wElement.size - 1].type = ENTRANCE;
			wElement.array[wElement.size - 1].connection = wKlemm.connection;
			wElement.array[wElement.size - 1].signal = wKlemm.signal;
			wElement.numEntence++;
		}
		else
			if (wKlemm.type == OUTPUT) {
				if (wKlemm.connection > 3 || wKlemm.connection < 0)
					throw std::invalid_argument("Invalid connection value");
				try {
					wElement.ChangeSpace();
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					throw std::invalid_argument("Dont have enough space!");
				}
				wElement.array[wElement.size - 1].type = OUTPUT;
				wElement.array[wElement.size - 1].connection = wKlemm.connection;
				wElement.array[wElement.size - 1].signal = wKlemm.signal;
				wElement.numOutput++;
			}
			else
				throw std::invalid_argument("Incorrect type");
	}

	LogicalElement& LogicalElement::operator=(LogicalElement &eqvl) {
		numEntence = eqvl.numEntence;
		numOutput = eqvl.numOutput;
		size = eqvl.size;
		delete[] array;
		try {
			array = new Klemm[size];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what();
			throw std::invalid_argument("Invalid argument");
		}
		for (register short i = 0; i < size; i++) {
			array[i].type = eqvl.array[i].type;
			array[i].connection = eqvl.array[i].connection;
			array[i].signal = eqvl.array[i].signal;
		}
	}

	Error CurrectString(const char *eqvlStr, char *workStr) {
		int i = 0;
		while (workStr[i] != '\0') {
			workStr[i] = tolower(workStr[i]);
			i++;
		}
		if(!strcmp(workStr, eqvlStr))
			return SUCCESS;
		return INVALID_VALUE;
	}

	void LogicalElement::ChangeSpace(void) {
		Klemm* newArray = nullptr, *deletePtr;

		try {
			newArray = new Klemm[size + 1];
		}
		catch (std::exception &ex) {
			throw std::invalid_argument("Array is too big");
		}
		
		for (int i = 0; i < size; i++) {
			newArray[i].connection = array[i].connection;
			newArray[i].signal = array[i].signal;
			newArray[i].type = array[i].type;
		}
		deletePtr = array;
		array = newArray;
		delete[] deletePtr;
		size++;
	}

	LogicalElement::~LogicalElement() {
		delete[] array;
	}
}