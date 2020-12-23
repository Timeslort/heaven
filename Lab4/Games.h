#ifndef _GAMES_H_
#define _GAMES_H_
#include "Players.h"

namespace Prog4 {
	
	struct Date {
		friend std::ostream& operator<<(std::ostream& output, const Date& outDate);
		friend std::istream& operator>>(std::istream& input, Date& inDate);
		Date();
		void SetDate(short int d, short int m, short int y);
	private:
		short int date;
		short int month;
		short int year;
	};

	class Game {
		friend std::istream& operator>>(std::istream& input, Game& inGame);
		friend std::ostream& operator<<(std::ostream& output, const Game* outGame);
	public:
		Game() :gameDate(), enemyTeamName("Noname"), numberPlayers(0), array(new Player*[Game::QOUTA]) {}
		Game(const Game&);
		Game& AddPlayer(const Player&);
		Game& RemovePlayer(int);
		~Game();
	private:
		static const int QOUTA = 10;
		Date gameDate;
		char enemyTeamName[20];
		short int numberPlayers;
		Player** array;
	};


}//Prog4

#endif
