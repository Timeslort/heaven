#ifndef _PLAYERS_H_
#define _PLAYERS_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <typeinfo>

namespace Prog4{
	
	class Player {
		friend std::ostream& operator<<(std::ostream& out, const Player& outP) { return outP.print(out); }
		friend std::istream& operator>>(std::istream& in, Player& inP) { return inP.input(in); }
	public:
		Player():playTime(0), penaltyTime(0), surname("Noname") {}
		virtual Player* clone() const = 0;
		void GetRole(void)const { std::cout << typeid(*this).name() << std::endl; }
		Player& SetPlayTime(int t) {
			playTime = t > 0 ? t : 0;
			return *this;
		}
		Player& SetPenaltyTime(int t) {
			penaltyTime = t > 0 ? t : 0;
			return *this;
		}
		Player& SetSurname(char* a) { 
				strcpy(surname,a);
				return *this;
		}
		Player& SetSurname(const char* a) {
				strcpy(surname, a);
				return *this;
		}
		virtual short int GetPlayTime(void) const { return playTime; }
		virtual short int GetPenaltyTime(void) const { return penaltyTime; }
		const char* GetSurname(void) const { return surname; }
		virtual void PrintSurname(void) const { std::cout << "Surname : " << surname << std::endl; }
		virtual ~Player() {}
	private:
		char surname[20];
		short int playTime; //in seconds
		short int penaltyTime; //in seconds
		//DEBUG
		virtual std::ostream& print(std::ostream&) const = 0;
		virtual std::istream& input(std::istream&) = 0;
	};

	class Defender : public Player {
		friend std::istream& operator>>(std::istream&in, Defender&inP) { return inP.input(in); }
		friend std::ostream& operator<<(std::ostream&out, const Defender&outP) { return outP.print(out); }
	public:
		Defender() :Player() {}
		Defender(short int a, short int b = 0 , char* = nullptr);
		Defender(const Defender& copy) {
			SetPlayTime(copy.GetPlayTime());
			SetPenaltyTime(copy.GetPenaltyTime());
			SetSurname(copy.GetSurname());
		}
		virtual Defender* clone(void) const { return new Defender(*this); }
		virtual ~Defender() {}
	protected:
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};

	class Goalkeeper : public Defender {
	public:
		friend std::istream& operator>>(std::istream& in, Goalkeeper& inP) { return inP.input(in); }
		friend std::ostream& operator<<(std::ostream& out, const Goalkeeper& outP) { return outP.print(out); }
		Goalkeeper():notReflThrows(0), reflThrows(0), Defender() {}
		Goalkeeper(const Goalkeeper&copy):reflThrows(copy.reflThrows),notReflThrows(copy.notReflThrows) {
			SetPlayTime(copy.GetPlayTime());
			SetPenaltyTime(copy.GetPenaltyTime());
			SetSurname(copy.GetSurname());
		}
		Goalkeeper(short int tr, short int ntr = 0);
		virtual Goalkeeper* clone() const { return new Goalkeeper(*this); }
		short int GetReflThrows(void) const { return reflThrows; }
		short int GetNotReflThrows(void) const { return notReflThrows; }
		virtual ~Goalkeeper() {}
	private:
		short int reflThrows;
		short int notReflThrows;
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};

	class Attack : public Defender {
		friend std::istream& operator>>(std::istream&in, Attack&inP) { return inP.input(in); }
		friend std::ostream& operator<<(std::ostream&out, const Attack&outP) { return outP.print(out); }
	public:
		Attack() :Defender(), effThrows(0), notEffThrows(0) {}
		Attack(const Attack&copy): effThrows(copy.effThrows),notEffThrows(copy.notEffThrows) {
			SetPlayTime(copy.GetPlayTime());
			SetPenaltyTime(copy.GetPenaltyTime());
			SetSurname(copy.GetSurname());
		}
		Attack(short int eff, short int neff = 0, char* = nullptr);
		virtual Attack* clone(void)const { return new Attack(*this); }
		short int GetEffThrows(void) const { return effThrows; }
		short int GetNotEffThrows(void) const { return notEffThrows; }
		virtual ~Attack() {}
	private:
		short int effThrows;
		short int notEffThrows;
		//DEBUG
		virtual std::istream& input(std::istream&);
		virtual std::ostream& print(std::ostream&) const;
	};


}//Prog4

#endif