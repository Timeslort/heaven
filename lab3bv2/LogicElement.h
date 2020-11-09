#ifndef _LOGICELEMENT_H_
#define _LOGICELEMENT_H_
#include"Klemm.h"
#include"Iterator.h"
#define LINE std::cout << "|----------------------------------------|" << std::endl

namespace Prog3 {

	class LogicElement {
		friend ConstLogicElementIt;
		friend std::istream& operator>>(std::istream&, LogicElement&);
		friend std::ostream& operator<<(std::ostream&, const LogicElement&);
	public:
		LogicElement() :size(0), numEntr(0), numOut(0), maxSize(LogicElement::QUOTA), array(new Klemm[LogicElement::QUOTA]) {}
		LogicElement(const LogicElement&);
		LogicElement(LogicElement&&);
		LogicElement(const Klemm&, int count);
		LogicElement(int Entr, int Out);
		//
		typedef ConstLogicElementIt Iterator;
		Iterator begin() { return ConstLogicElementIt(this->array); }
		Iterator end() { return ConstLogicElementIt(this->array + this->size); }
		//Geter's
		int getEntrace(void) const { return numEntr; }
		int getOut(void) const { return numOut; }
		int getSize(void) const { return size; }
		Klemm& operator[](const int indx);
		const Klemm& operator[](const int indx) const;
		//Seter's
		void operator()(int num, char* tp, int con, char sig);
		void operator()(int num, const char* tp, int con, char sig);
		void increaseConnection(int indx);
		void decreaseConnection(int indx);
		//
		const LogicElement& operator=(const LogicElement&);
		LogicElement& operator=(LogicElement&&); //перемещеннием
		LogicElement& operator+=(char* type);
		LogicElement& operator+=(Klemm&);
		//
		std::ostream& print(std::ostream&) const;
		//
		~LogicElement() { delete[] array; }
	private:
		static const int QUOTA = 10;
		int numEntr;
		int numOut;
		int size;
		int maxSize;
		Klemm* array;
		void changeSpace(Klemm*& array);
		void redefinition(LogicElement&);
	};


}//namespace Prog3
#endif