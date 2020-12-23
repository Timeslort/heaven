#ifndef _PLAYERS_H_
#define _PLAYERS_H_
#include <iostream>
//#include <typeinfo>

namespace Prog4{
	
	class Player {
		friend std::ostream& operator<<(std::ostream& out, const Player& outP) { return outP.print(out); }
		friend std::istream& operator>>(std::istream& in, Player& inP) { return inP.input(in); }
	public:
		Player() {}
		virtual Player* clone() const = 0;
		virtual void GetRole(void)const = 0;
		short int GetPlayTime(void) const { return playTime; }
		short int GetPenaltyTime(void) const { return penaltyTime; }
		virtual ~Player() {}
	protected:
		char surname[20];
		short int playTime; //in seconds
		short int penaltyTime; //in seconds
		//DEBUG
		virtual std::ostream& print(std::ostream&) const = 0;
		virtual std::istream& input(std::istream&) = 0;
	};

	class Goalkeeper : public Player {
		friend std::istream& operator>>(std::istream&, Goalkeeper&);
		friend std::ostream& operator<<(std::ostream&, const Goalkeeper&);
	public:
		Goalkeeper();
		virtual Goalkeeper* clone();
		virtual void GetRole(void) const;
		short int GetReflThrows(void) const { return reflThrows; }
		short int GetNotReflThrows(void) const { return notReflThrows; }
		virtual ~Goalkeeper() {}
	protected:
		short int reflThrows;
		short int notReflThrows;
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};

	class Defender : public Player {
		friend std::istream& operator>>(std::istream&, Defender&);
		friend std::ostream& operator<<(std::ostream&, const Defender&);
	public:
		Defender();
		virtual Defender* clone(void);
		virtual void GetRole(void)const;
		virtual ~Defender() {}
	protected:
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};

	class Attack : public Player {
		friend std::istream& operator>>(std::istream&, Attack&);
		friend std::ostream& operator<<(std::ostream&, const Attack&);
	public:
		Attack();
		virtual Attack* clone(void);
		virtual void GetRole(void)const;
		short int GetEffThrows(void) const { return effThrows; }
		short int GetNotEffThrows(void) const { return notEffThrows; }
		virtual ~Attack() {}
	protected:
		short int effThrows;
		short int notEffThrows;
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};


}//Prog4

#endif