#include<iostream>
#include"Klemm.h"
#include<string.h>
#include<exception>

namespace Prog3 {

	Klemm::Klemm(const char* tp, int con, char sig) {
		if (tp != "entrance" && tp != "output")
			throw std::invalid_argument("Invalid type!");
		type = tp;

		if (con == 0 && sig != 'X')
			throw std::invalid_argument("If connection zero, signal state is X!");
		if (tp == "entrance" && con != 0 && con != 1)
			throw std::invalid_argument("Invalid connection!");
		if (tp == "output" && (con < 0 || con > 3))
			throw std::invalid_argument("Invalid connection!");
		connection = con;

		if (sig != '1' && sig != '0' && sig != 'X')
			throw std::invalid_argument("Invalif signal");
		if (sig == 'X' && con > 0)
			throw std::invalid_argument("Invalif signal");
		signal = sig;
	}

	std::istream& operator>>(std::istream& input, Klemm& inKlm) {
		char newType[20], newSignal;
		int newCon;
		std::cout << "Enter type (output, entrance) : ";
		input >> newType;
		input.clear();
		while (input.get() != '\n');
		try {
			inKlm.setType(newType);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::invalid_argument("Can't do it");
		}

		std::cout << std::endl << "Enter number of connection for output [0, 3], entrance[0, 1] : ";
		if (GetInt(newCon))
			throw std::invalid_argument("Can't do it");
		try {
			inKlm.setConnection(newCon);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::invalid_argument("Can't do it");
		}

		if (newCon == 0)
			inKlm.signal = 'X';
		else {
			std::cout << std::endl << "Enter signal state (0, 1):" << std::endl;
			input >> newSignal;
			input.clear();
			while (input.get() != '\n');
			if (newSignal == '1' || newSignal == '0')
				inKlm.signal = newSignal;
			else
				throw std::invalid_argument("Can't do it");
		}
		return input;
	}

	std::ostream& operator<<(std::ostream& output, const Klemm& outKlm) {
		output << "Klemm type : " << outKlm.type << std::endl
			<< "Number of connection : " << outKlm.connection << std::endl
			<< "Signal state : " << outKlm.signal << std::endl;
		return output;
	}

	void Klemm::setType(char* tp) {
		if (CorrectString("entrance", tp))
			if (CorrectString("output", tp))
				throw std::invalid_argument("Invalid type");
			else
				type = "output";
		else
			type = "entrance";
	}

	void Klemm::setType(const char* tp) {
		if (CorrectString("entrance", tp))
			if (CorrectString("output", tp))
				throw std::invalid_argument("Invalid type");
			else
				if (-1 < connection && connection < 4)
					type = "output";
				else
					throw std::invalid_argument("Invalid type with this connection!");
		else
			if(connection == 1 || connection == 0)
				type = "entrance";
			else 
				throw std::invalid_argument("Invalid type with this connection!");
	}

	void Klemm::setSignal(char sig) {
		if (connection == 0) {
			std::cout << "If conncetion zero, signal state X" << std::endl;
			signal = 'X';
		}
		else {
			if (sig == '1' || sig == '0')
				signal = sig;
			else
				throw std::invalid_argument("Invalid signal");
		}
	}

	void Klemm::setConnection(const int con) {
		if (type == "entrance")
			if (con != 0 && con != 1)
				throw std::invalid_argument("Invalid number of connection");
			else {
				connection = con;
				if (con == 0)
					signal = 'X';
			}
		else
			if (con < 0 || con > 3)
				throw std::invalid_argument("Invalid number of connection");
			else {
				connection = con;
				if (con == 0)
					signal = 'X';
			}
	}

	int operator++(Klemm& preIncr) {
		int con;
		con = preIncr.getConnection() + 1;
		try {
			preIncr.setConnection(con);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << " because it's max!" << std::endl;
			throw std::out_of_range("Out of range");
		}
		return con;
	}

	int operator++(Klemm& postIncr, int) {
		int con;
		con = postIncr.getConnection();
		try {
			postIncr.setConnection(con + 1);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << " because it's max!" << std::endl;
			throw std::out_of_range("Out of range");
		}
		return con;
	}

	int operator--(Klemm& preDecr) {
		int con;
		con = preDecr.getConnection() - 1;
		try {
			preDecr.setConnection(con);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << "because it's min!" << std::endl;
			throw std::out_of_range("Out of range");
		}
		if (con == 0)
			preDecr.setSignal('X');
		return con;
	}

	int operator--(Klemm& postDecr, int) {
		int con;
		con = postDecr.getConnection();
		try {
			postDecr.setConnection(con - 1);
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << "because it's min!" << std::endl;
			throw std::out_of_range("Out of range");
		}
		if (con == 0)
			postDecr.setSignal('X');
		return con;
	}

	Error GetInt(int& a) {
		std::cin >> a;
		if (!std::cin.good()) {
			std::cin.clear();
			while (std::cin.get() != '\n');
			return INCORRECT_ARGUMENT;
		}
		return SUCCESS;
	}

	Error CorrectString(const char* str, char* eqvl) {
		for (int i = 0; i < strlen(eqvl); i++)
			eqvl[i] = tolower(eqvl[i]);
		if (!strcmp(str, eqvl))
			return SUCCESS;
		return INCORRECT_ARGUMENT;
	}

	Error CorrectString(const char* str, const char* eqvl) {
		if (!strcmp(str, eqvl))
			return SUCCESS;
		return INCORRECT_ARGUMENT;
	}

}//namespace Prog3