#ifndef _TEAM_H_
#define _TEAM_H_
#include "Games.h"

namespace Prog4{

	class Team {
		friend std::ostream& operator<<(std::ostream& output, const Team outT);
		friend std::istream& operator>>(std::istream& input, Team inT);
	public:
		Team();
		Team& AddGame(const Game&);
		const Game& FindElement(const Date&) const;
		Team& RemoveGame(const Date&);
		void GetTable(void)const;
		~Team();
	private:
		char trainer[20];
		char nickname[20];
		Game* table;
	};


}//Prog4

#endif
