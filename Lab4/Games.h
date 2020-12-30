#ifndef _GAMES_H_
#define _GAMES_H_
#include "Players.h"
#include "MyVector.h"

namespace Prog4 {
	
	struct Date {
		friend std::ostream& operator<<(std::ostream& output, const Date& outDate);
		friend std::istream& operator>>(std::istream& input, Date& inDate);
		Date() :day(6), month(9), year(1337) {}
		Date(short int d, short int m, short int y);
		Date(const Date& copy) :day(copy.day), month(copy.month), year(copy.year) {}
		short int GetDay(void) const { return day; }
		short int GetMonth(void) const { return month; }
		short int GetYear(void) const { return year; }
		void SetDate(short int d, short int m, short int y);
	private:
		short int day;
		short int month;
		short int year;
	};

	class Game {
		friend std::istream& operator>>(std::istream& input, Game& inGame);
		friend std::ostream& operator<<(std::ostream& output, const Game& outGame);
	public:
		Game() :gameDate(), enemyTeamName("Noname"), numberPlayers(0), array() {}
		Game(const Game&copy);
	//	Game(Game&&);
		Game* clone() const { return new Game(*this); }
		Game& AddPlayer(Player*&);
		Game& RemovePlayer(int);
		void PrintPlayers(void) {
			for (int i = 0; i < numberPlayers; ++i) {
				std::cout << i + 1 << "." << *array[i] << std::endl;
			}
		}
		short int GetNumberOfPlayer(void) const { return numberPlayers; }
		const Date& GetDate(void) const { return gameDate; }
		~Game() {}
	private:
		Date gameDate;
		char enemyTeamName[20];
		short int numberPlayers;
		MyVector<Player*> array;
	};


}//Prog4

#endif
