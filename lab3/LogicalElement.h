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
		Klemm(int tip = 0, int conect = 0, int sig = 3): type(tip), connection(conect), signal(sig) {}
	};

	class LogicalElement {
	public:
		LogicalElement(int in = 0, int out = 0);
		LogicalElement(Klemm &, int count);
		void GetKlemm(void);
		void GetKlemm(int) const;
		void GetAllKlemm(void) const;
		void SetKlemm(int);
		void Redefinition(void);
		void AddKlemm(void);
		void IncreaseConnection(int);
		void DecreaseConnection(int);
	private:
		Klemm array[20];
		int numEntence;
		int numOutput;
		Error GetSignal(int &);
		Error CurrectChoice(int&, int start, int end);
	};
}