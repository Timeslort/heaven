#include<iostream>
#include"LogicElement.h"
#include<exception>
#include<assert.h>
#include<stdlib.h>

namespace Prog3 {

	LogicElement::LogicElement(const LogicElement& copy) : numEntr(copy.numEntr), numOut(copy.numOut), size(copy.size), maxSize(copy.maxSize) {
		array = new Klemm[size];
		assert(array);
		for (int i = 0; i < size; i++) {
			array[i].setType(copy[i].getType());
			array[i].setConnection(copy[i].getConnection());
			array[i].setSignal(copy[i].getSignal());
		}
	}

	LogicElement::LogicElement(LogicElement&& mov) : numEntr(mov.numEntr), numOut(mov.numOut), size(mov.size), maxSize(mov.maxSize) {
		array = mov.array;
		mov.array = nullptr;
	}

	LogicElement::LogicElement(const Klemm& copy, int count) : size(count), maxSize(count) {
		array = new Klemm[size];
		const char* nType = copy.getType();
		int nCon = copy.getConnection();
		char nSig = copy.getSignal();
		if (nType == "entrance") {
			numEntr = count;
		}
		else
			if (nType == "output")
				numOut = count;
			else
				throw std::invalid_argument("Invalid type");

		for (int i = 0; i < size; i++) {
			array[i].setType(nType);
			array[i].setConnection(nCon);
			array[i].setSignal(nSig);
		}
	}

	LogicElement::LogicElement(int Entr, int Out) :numEntr(Entr), numOut(Out) {
		size = Entr + Out;
		maxSize = size;
		array = new Klemm[size];
		assert(array);
		for (int i = 0; i < Entr; i++) {
			array[i].setType("entrance");
		}
		for (int i = Entr; i < Entr + Out; i++) {
			array[i].setType("output");
		}
	}

	Klemm& LogicElement::operator[](const int indx) {
		if (indx < 0 || indx > size)
			throw::std::out_of_range("Invalid index");

		return array[indx];
	}

	const Klemm& LogicElement::operator[](const int indx) const {
		if (indx < 0 || indx > size)
			throw::std::out_of_range("Invalid index");

		return array[indx];
	}

	std::istream& operator>>(std::istream& input, LogicElement& inEl) {
		for (int i = 0; i < inEl.size; i++) {
			try {
				input >> inEl.array[i];
			}
			catch (std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		return input;
	}

	std::ostream& operator<<(std::ostream& output, const LogicElement& outEl) {
		for (int i = 0; i < outEl.size; i++) {
			LINE;
			output << "     Klemm #" << i + 1 << std::endl
				<< outEl.array[i] << std::endl;;
		}
		LINE;
		return output;
	}

	void LogicElement::operator()(int num, char* tp, int con, char sig) {
		int index = num - 1;
		if (CorrectString("entrance", tp))
			if ((CorrectString("output", tp)))
				throw std::invalid_argument("Invalide type");
			else {
				array[index].setType(tp);
				try {
					array[index].setConnection(con);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					throw std::invalid_argument("Can't change!");
				}
				if (con != 0) {
					try {
						array[index].setSignal(sig);
					}
					catch (std::exception& ex) {
						std::cout << ex.what() << std::endl;
						throw std::invalid_argument("Can't change!");
					}
				}
			}
		else {
			if (con == 1 || con == 0) {
				array[index].setConnection(con);
				array[index].setType(tp);
				if (con != 0) {
					try {
						array[index].setSignal(sig);
					}
					catch (std::exception& ex) {
						std::cout << ex.what() << std::endl;
						throw std::invalid_argument("Can't change!");
					}
				}
			}
		}
	}

	void LogicElement::operator()(int num, const char* tp, int con, char sig) {
		int index = num - 1;
		if (CorrectString("entrance", tp))
			if ((CorrectString("output", tp)))
				throw std::invalid_argument("Invalide type");
			else {
				array[index].setType(tp);
				try {
					array[index].setConnection(con);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
					throw std::invalid_argument("Can't change!");
				}
				if (con != 0) {
					try {
						array[index].setSignal(sig);
					}
					catch (std::exception& ex) {
						std::cout << ex.what() << std::endl;
						throw std::invalid_argument("Can't change!");
					}
				}
			}
		else {
			if (con == 1 || con == 0) {
				array[index].setConnection(con);
				array[index].setType(tp);
				if (con != 0) {
					try {
						array[index].setSignal(sig);
					}
					catch (std::exception& ex) {
						std::cout << ex.what() << std::endl;
						throw std::invalid_argument("Can't change!");
					}
				}
			}
			else 
				throw std::invalid_argument("Can't change!Ivalid values!");
		}
	}

	const LogicElement& LogicElement::operator=(const LogicElement& eqvl) {
		if (&eqvl != this) { // проверка на а = а
			numEntr = eqvl.numEntr;
			numOut = eqvl.numOut;
			size = eqvl.size;
			delete[] array;
			array = new Klemm[size];
			assert(array);
			for (int i = 0; i < size; i++) {
				array[i].setType(eqvl.array[i].getType());
				array[i].setConnection(eqvl.array[i].getConnection());
				array[i].setSignal(eqvl.array[i].getSignal());
			}
		}
		return *this; // x = y = z
	}

	LogicElement& LogicElement::operator=(LogicElement&& El) {
		int tmp = numEntr;
		numEntr = El.numEntr;
		El.numEntr = tmp;

		tmp = numOut;
		numOut = El.numOut;
		El.numOut = tmp;

		tmp = size;
		size = El.size;
		El.size = tmp;

		tmp = maxSize;
		maxSize = El.maxSize;
		El.maxSize = tmp;

		Klemm* ptr = array;
		array = El.array;
		El.array = ptr;
		return *this;
	}

	void LogicElement::operator+=(char* tp) {
		if (CorrectString("entrance", tp))
			if (CorrectString("output", tp))
				throw std::invalid_argument("Invalid type");
			else {
				if (size >= maxSize)
					changeSpace(array);
				array[size].setType("output");
				size++;
				numOut++;
			}
		else {
			if (size >= maxSize)
				changeSpace(array);
			array[size].setType("entrance");
			size++;
			numEntr++;
		}
	}

	void LogicElement::operator+=(Klemm& plus) {
		if (CorrectString("entrance", plus.getType()))
			if (CorrectString("output", plus.getType()))
				throw std::invalid_argument("Invalid type");
			else {
				if (size >= maxSize)
					changeSpace(array);
				array[size].setType("output");
				array[size].setConnection(plus.getConnection());
				array[size].setSignal(plus.getSignal());
				size++;
				numOut++;
			}
		else {
			if (size >= maxSize)
				changeSpace(array);
			array[size].setType("entrance");
			array[size].setConnection(plus.getConnection());
			array[size].setSignal(plus.getSignal());
			size++;
			numEntr++;
		}
	}

	void LogicElement::changeSpace(Klemm*& arr) {
		Klemm* delArr = arr;

		arr = new Klemm[maxSize += LogicElement::QUOTA];
		assert(arr);
		for (int i = 0; i < size; i++) {
			arr[i].setType(delArr[i].getType());
			arr[i].setConnection(delArr[i].getConnection());
			arr[i].setSignal(delArr[i].getSignal());
		}
		delete[] delArr;
	}

}//namespace Prog3