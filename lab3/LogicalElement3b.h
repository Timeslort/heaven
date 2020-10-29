#pragma once

namespace Prog3 {
	enum Type {
		OUTPUT, //0
		ENTRANCE //1
	};

	enum Error {
		INVALID_VALUE = 1,
		SUCCESS = 0
	};

	struct Klemm {
		int type;
		int connection;
		int signal;
		Klemm(int tip = 0, int conect = 0, int sig = 3) : type(tip), connection(conect), signal(sig) {}
	};

	std::ostream& operator<<(std::ostream&,const Klemm&);
	std::istream& operator>>(std::istream&, Klemm&);
	Error CurrectString(const char* eqvlStr, char* workStr);

	class LogicalElement {
	public:
		LogicalElement(int in = 0, int out = 0);
		LogicalElement(Klemm&, int count);
		LogicalElement(LogicalElement &);
		void GetKlemm(void);
		void GetKlemm(int) const;
		void GetAllKlemm(void) const;
		void SetKlemm(int);
		void Redefinition(void);
		void AddKlemm(void);
		void IncreaseConnection(int);
		void DecreaseConnection(int);
		friend std::ostream& operator<<(std::ostream &, const LogicalElement&);
		friend std::istream& operator>>(std::istream &, LogicalElement &);
		friend void operator+=(LogicalElement&, char *type);
		friend void operator+=(LogicalElement&, Klemm&);
		LogicalElement &operator=(LogicalElement&);
		Klemm &operator[](const int);
		void operator()(int numOfKlmm, char* type, int con, char sgnl);
		~LogicalElement();
	private:
		Klemm* array;
		//Klemm array[20];
		int numEntence;
		int numOutput;
		int size;
		Error GetSignal(int&);
		Error CurrectChoice(int&, int start, int end);
		void ChangeSpace(void);
	};
}