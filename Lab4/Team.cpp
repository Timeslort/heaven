#include "Team.h"
#include <exception>

namespace Prog4 {

	int GetInt3(short int& a) {
		std::cin >> a;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return 1;
		}
		return 0;
	}

	Team::Team(char* trName, char* tmName):table(new Game*[Team::QOUTA]), maxGames(Team::QOUTA), numberGames(0) {
		Game a;
		for (int i = 0; i < maxGames; ++i)
			table[i] = a.clone();
		strcpy(trainer, trName);
		strcpy(nickname, tmName);
	}

	Team& Team::AddGame(const Game &adding) {
		if (maxGames <= numberGames) {
			Game** delarr = table;
			table = new Game* [numberGames += Team::QOUTA];
			assert(table);
			for (int i = 0; i < numberGames; ++i)
				table[i] = delarr[i]->clone();
			delete[] delarr;
		}
		table[numberGames] = adding.clone();
		++numberGames;

		return *this;
	}
	
	Game& Team::FindElement(const Date&date) const {
		Date objDate;
		for (int i = 0; i < numberGames; i++) {
			objDate = (*table[i]).GetDate();
			if (objDate.GetDay() == date.GetDay())
				if (objDate.GetMonth() == date.GetMonth())
					if (objDate.GetYear() == date.GetYear())
						return *table[i];
		}
		throw std::invalid_argument("Can't find!");
	}

	short int Team::FindIndex(const Date& date) const {
		Date objDate;
		for (int i = 0; i < numberGames; i++) {
			objDate = (*table[i]).GetDate();
			if (objDate.GetDay() == date.GetDay())
				if (objDate.GetMonth() == date.GetMonth())
					if (objDate.GetYear() == date.GetYear())
						return i;
		}
		throw std::invalid_argument("Can't find!");
	}

	Team& Team::RemoveGame(const Date&date) {
		short int index;
		try {
			index = FindIndex(date);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::out_of_range("incorrect date");
		}
		delete table[index];
		//array[index] = nullptr;	
		for (int i = index; i < numberGames; ++i)
			table[i] = table[i + 1];
		--numberGames;
		
		return *this;
	}

	void Team::GetTable(void)const {
		std::cout << "|------------------------|" << std::endl;
		for (int i = 0; i < numberGames; ++i) {
			std::cout << *table[i];
			std::cout << "|------------------------|" << std::endl;
		}
	}

	std::ostream& operator<<(std::ostream& output, const Team& outT) {
		output << "Trainer name : " << outT.trainer << std::endl
			<< "Team name : " << outT.nickname << std::endl;
		return output;
	}

	std::istream& operator>>(std::istream& input, Team& inT) {
		Game** dellarr = inT.table;
		short int correctInput;
		char name[20];

		std::cout << "Enter numbers of Games : ";
		while (GetInt3(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		if (correctInput > inT.maxGames) {
			inT.maxGames = correctInput;
			inT.table = new Game * [inT.maxGames];
			assert(inT.table);
			delete[] dellarr;
		}
		for (int i = 0; i < correctInput; ++i) {
			input >> *inT.table[i];
		}

		std::cout << "Enter team tag : ";
		input >> name;
		input.clear();
		while (input.get() != '\n');
		strcpy(inT.nickname, name);
		

		std::cout << "Enter trainer name : ";
		input >> name;
		input.clear();
		while (input.get() != '\n');
		strcpy(inT.trainer, name);
		
		inT.numberGames = correctInput;
		return input;
	}

}//namespace prog4