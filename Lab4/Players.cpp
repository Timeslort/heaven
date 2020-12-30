#include "Players.h"

namespace Prog4 {

	int GetInt(short int& a) {
		std::cin >> a;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return 1;
		}
		return 0;
	}

	//Goalkeeper
	Goalkeeper::Goalkeeper(short int tr, short int ntr):Defender(){
		notReflThrows = ntr > 0 ? ntr : 0;
		reflThrows = tr > 0 ? tr : 0;
	}

	std::istream& Goalkeeper::input(std::istream&in) {
		short int correctInput = -1;

		this->Defender::input(in);
		std::cout << "Enter reflected throws : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		this->reflThrows = correctInput;
		correctInput = -1;
		std::cout << "Enter not reflected throws : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		this->notReflThrows = correctInput;
		return in;
	}

	std::ostream& Goalkeeper::print(std::ostream& out) const {
		this->Defender::print(out)
			<< "Reflected throws : " << this->reflThrows << std::endl
			<< "Not reflected throws : " << this->notReflThrows << std::endl;
		return out;
	}
	//Attack

	Attack::Attack(short int eff, short int neff, char* name) {
		effThrows = eff > 0 ? eff : 0;
		notEffThrows = neff > 0 ? neff : 0;
		if (name)
			SetSurname(name);
	}

	std::istream& Attack::input(std::istream&in) {
		short int correctInput = -1;

		this->Defender::input(in);
		std::cout << "Enter effective throws : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		this->effThrows = correctInput;
		correctInput = -1;
		std::cout << "Enter not effective throws : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		this->notEffThrows = correctInput;
		return in;
	}

	std::ostream& Attack::print(std::ostream&out) const {
		this->Defender::print(out)
			<< "Reflected throws : " << this->effThrows << std::endl
			<< "Not reflected throws : " << this->notEffThrows << std::endl;
		return out;
	}

	//Defender
	Defender::Defender(short int a, short int b, char* name) {
		SetPlayTime(a);
		SetPenaltyTime(b);
		if (name)
			SetSurname(name);
	}

	std::istream& Defender::input(std::istream&in) {
		char name[20];
		short int correctInput = -1;
		std::cout << "Enter Surname : " << std::endl;
		in >> name;
		in.clear();
		while (in.get() != '\n');
		SetSurname(name);
		std::cout << "Enter play time : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		SetPlayTime(correctInput);
		correctInput = -1;
		std::cout << "Enter penalty time : " << std::endl;
		while (GetInt(correctInput) || correctInput < 0) {
			std::cout << "Error" << std::endl;
		}
		SetPenaltyTime(correctInput);
		return in;
	}

	std::ostream& Defender::print(std::ostream&out) const {
		this->PrintSurname();
		out << "Play time : " << this->GetPlayTime() << std::endl
			<< "Penalty time : " << this->GetPenaltyTime() << std::endl;
		return out;
	}

}//namespace prog4