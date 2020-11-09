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
			if (!InCorrectString(inEl.array[i].getType(), "entrance")) {
				try {
					input >> inEl.array[i];
				}
				catch (std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
		}
		inEl.redefinition(inEl);
		return input;
	}

	std::ostream& operator<<(std::ostream& output, const LogicElement& outEl) {
		return outEl.print(output);
	}

	void LogicElement::operator()(int num, char* tp, int con, char sig) {
		int index = num - 1;
		if (InCorrectString("entrance", tp))
			if ((InCorrectString("output", tp)))
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
				redefinition(*this);
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
				redefinition(*this);
			}
		}
	}

	void LogicElement::operator()(int num, const char* tp, int con, char sig) {
		int index = num - 1;
		if (InCorrectString("entrance", tp))
			if ((InCorrectString("output", tp)))
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
				redefinition(*this);
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
				redefinition(*this);
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

	LogicElement& LogicElement::operator+=(char* tp) {
		if (InCorrectString("entrance", tp))
			if (InCorrectString("output", tp))
				throw std::invalid_argument("Invalid type");
			else {
				if (size >= maxSize)
					changeSpace(array);
				array[size].setType("output");
				size++;
				numOut++;
				redefinition(*this);
			}
		else {
			if (size >= maxSize)
				changeSpace(array);
			array[size].setType("entrance");
			size++;
			numEntr++;
			redefinition(*this);
		}
		return *this;
	}

	LogicElement& LogicElement::operator+=(Klemm& plus) {
		if (InCorrectString("entrance", plus.getType()))
			if (InCorrectString("output", plus.getType()))
				throw std::invalid_argument("Invalid type");
			else {
				if (size >= maxSize)
					changeSpace(array);
				array[size].setType("output");
				array[size].setConnection(plus.getConnection());
				array[size].setSignal(plus.getSignal());
				size++;
				numOut++;
				redefinition(*this);
			}
		else {
			if (size >= maxSize)
				changeSpace(array);
			array[size].setType("entrance");
			array[size].setConnection(plus.getConnection());
			array[size].setSignal(plus.getSignal());
			size++;
			numEntr++;
			redefinition(*this);
		}
		return *this;
	}

	void LogicElement::increaseConnection(int indx) {
		try {
			this->array[indx]++;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::invalid_argument(" ");
		}
		this->redefinition(*this);
	}

	void LogicElement::decreaseConnection(int indx) {
		try {
			this->array[indx]--;
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
			throw std::invalid_argument(" ");
		}
		this->redefinition(*this);
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

	void LogicElement::redefinition(LogicElement &rEl) {
		register int i;
		int countZero = 0, countOne = 0, countOutZ = 0, check = -1;

		for (i = 0; i < rEl.size; i++) {
			if (!InCorrectString(rEl.array[i].getType(), "entrance")) {
				if (rEl.array[i].getSignal() == '1')
					countOne++;
				if (rEl.array[i].getSignal() == '0')
					countZero++;
			}
			else {
				if (rEl.array[i].getSignal() == '0')
					countOutZ++;
			}
		}

		if (countZero == rEl.numEntr && countZero != 0)
			check = 1;
		if (countOne)
			check = 0;
		if (countZero + countOutZ == rEl.size)
			check = 2;

		for (i = 0; i < rEl.size; i++) {
			if (check == 2)
				rEl.array[i].setSignal('X');
			else {
				if (check == 1) {
					if (!InCorrectString(rEl.array[i].getType(), "output"))
						rEl.array[i].setSignal('1');
				}
				else if (check == 0)
					if (!InCorrectString(rEl.array[i].getType(), "output"))
						rEl.array[i].setSignal('0');
			}
		}
	}

	std::ostream& LogicElement::print(std::ostream& output) const {
		for (int i = 0; i < size; i++) {
			LINE;
			output << "     Klemm #" << i + 1 << std::endl;
			array[i].Klemm::print(output) << std::endl;
		}
		LINE;
		return output;
	}

}//namespace Prog3