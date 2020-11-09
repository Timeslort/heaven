#ifndef _KLEMM_H_
#define _KLEMM_H_
#include <istream>


namespace Prog3 {
	enum Error {
		SUCCESS,
		INCORRECT_ARGUMENT,
		INCORRECT_CONNECTION = -10
	};

	class Klemm {
		friend std::istream& operator>>(std::istream&, Klemm&);
		friend std::ostream& operator<<(std::ostream&, const Klemm&);
		friend Klemm operator++(Klemm&);
		friend Klemm operator++(Klemm&, int);
		friend Klemm operator--(Klemm&);
		friend Klemm operator--(Klemm&, int);
	public:
		Klemm() :type("undef"), signal('X'), connection(0) {}
		Klemm(const char* tp, int con, char sig);
		//geter's
		const char* getType(void) const { return type; }
		int getConnection(void) const { return connection; }
		char getSignal(void) const { return signal; }
		//seter's
		void setType(char*);
		void setType(const char*);
		void setSignal(char);
		void setConnection(const int);
		//
		std::ostream &print(std::ostream &) const;
	private:
		const char* type;
		char signal;
		int connection;
	};

	Error InCorrectString(const char* str, char* eqvl);
	Error InCorrectString(const char* str, const char* eqvl);
	Error GetInt(int&);
}// namespace Prog3
#endif
