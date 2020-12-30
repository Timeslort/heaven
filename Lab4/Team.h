#ifndef _TEAM_H_
#define _TEAM_H_
#include "Games.h"
#include<assert.h>
#include<stdlib.h>

namespace Prog4{

	class Team {
		friend std::ostream& operator<<(std::ostream& output, const Team& outT);
		friend std::istream& operator>>(std::istream& input, Team &inT);
	public:
		Team() :trainer("Noname"), nickname("Wolfs"), table(new Game*[Team::QOUTA]), maxGames(Team::QOUTA), numberGames(0) {
			Game a;
			for (int i = 0; i < maxGames; ++i)
				table[i] = a.clone();
		}
		Team(char* trName, char* tmName);
		Team& AddGame(const Game&);
		Game& FindElement(const Date&) const;
		short int FindIndex(const Date&) const;
		Team& RemoveGame(const Date&);
		void GetTable(void)const;
		~Team() { delete[] table; }
	private:
		static const int QOUTA = 10;
		short int maxGames;
		short int numberGames;
		char trainer[20];
		char nickname[20];
		Game** table;
	};


}//Prog4

#endif
