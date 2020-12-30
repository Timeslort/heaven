#include"Games.h"
#include<cstring>
#include<assert.h>
#include<stdlib.h>

namespace Prog4{

	int GetInt2(short int& a) {
		std::cin >> a;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return 1;
		}
		return 0;
	}

//Date
	Date::Date(short int d, short int m, short int y) {
		day = d > 0 && d < 31 ? d : 0;
		month = m > 0 && m < 12 ? m : 0;
		year = y > 0 && y < 2077 ? y : 0;
	}

	void Date::SetDate(short int d, short int m, short int y) {
		day = d > 0 && d < 31 ? d : 0;
		month = m > 0 && m < 12 ? m : 0;
		year = y > 0 && y < 2077 ? y : 0;
	}

	std::ostream& operator<<(std::ostream& output, const Date& outDate) {
		output << outDate.day << "." << outDate.month << "." << outDate.year;
		return output;
	}

	std::istream& operator>>(std::istream& input, Date& inDate) {
		short int number;
		std::cout << "enter day ";
		input >> number;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
		else
			inDate.day = number > 0 && number < 31 ? number : 1;

		std::cout << "enter month ";
		input >> number;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
		else
			inDate.month = number > 0 && number < 12 ? number : 1;

		std::cout << "enter year ";
		input >> number;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
			else 
			inDate.year = number > 1900 && number < 2077 ? number : 2007;
		return input;
	}

//Game
	Game::Game(const Game& copy):gameDate(copy.gameDate), numberPlayers(copy.numberPlayers), array(copy.array) {
		strcpy(enemyTeamName, copy.enemyTeamName);
		for (int i = 0; i < numberPlayers; i++) {
			array[i] = (*copy.array[i]).clone();
		}
	}

	/*Game::Game(Game&&mov):gameDate(mov.gameDate), numberPlayers(mov.numberPlayers) {
		strcpy(enemyTeamName, mov.enemyTeamName);
		array = mov.array;
		mov.array = nullptr;
	}*/


	
	Game& Game::AddPlayer(Player *&adding) {
		array.push_back(adding->clone());
		++numberPlayers;

		return *this;
	}

	Game& Game::RemovePlayer(int index) {
		if (index >= 0 && index <= numberPlayers) {
			delete array[index];
			//array[index] = nullptr;	
			array.erase(index);
			--numberPlayers;
		}
		return *this;
	}

	std::istream& operator>>(std::istream& input, Game& inGame) {
		Goalkeeper P1;
		Defender P2;
		Attack P3;
		short int correctInput, choice;
		char name[20];

		std::cout << "Enter numbers of players : ";
		while (GetInt2(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		MyVector <Player*> arr(correctInput);
		inGame.array = arr;

		for (int i = 0; i < correctInput; ++i) {
			std::cout << "Enter choice : 1.Goalkeeper, 2.Defender, 3.Attack ";
			while (GetInt2(choice) || choice < 0 || choice > 3) {
				std::cout << "Error" << std::endl;
			}
			switch (choice) {
			case 1:
				inGame.array[i] = P1.clone();
				break;
			case 2:
				inGame.array[i] = P2.clone();
				break;
			case 3:
				inGame.array[i] = P3.clone();
				break;
			}
			input >> *inGame.array[i];
		}
		input >> inGame.gameDate;

		std::cout << "Enter enemy team tag : ";
		input >> name;
		input.clear();
		while (input.get() != '\n');
		strcpy(inGame.enemyTeamName, name);
		inGame.numberPlayers = correctInput;

		return input;
	}

	std::ostream& operator<<(std::ostream& output, const Game& outGame) {
		output << "Date : " << outGame.gameDate << std::endl
			<< "Enemy team tag : " << outGame.enemyTeamName << std::endl
			<< "Line-up" << std::endl;
		for (int i = 0; i < outGame.numberPlayers; ++i) {
			output << i + 1 << ".";
			(*outGame.array[i]).PrintSurname();
			(*outGame.array[i]).GetRole();
		}
		return output;
	}


}//namespace prog4