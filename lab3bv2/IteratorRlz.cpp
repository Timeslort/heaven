#include<iostream>
#include"Iterator.h"

namespace Prog3 {

	const Klemm& ConstLogicElementIt::operator *() const {
		if (cur)
			return *cur;
		throw std::invalid_argument("Ilegal value gor LogicElement iteartor!");
	}

	ConstLogicElementIt& ConstLogicElementIt::operator++() {
		++cur;
		return *this;
	}

	ConstLogicElementIt ConstLogicElementIt::operator++(int) {
		ConstLogicElementIt tmp;
		tmp.cur = cur;
		cur++;
		return tmp;
	}

	int ConstLogicElementIt::operator!=(const ConstLogicElementIt &it)const {
		return cur != it.cur;
	}

	int ConstLogicElementIt::operator==(const ConstLogicElementIt &it)const {
		return cur == it.cur;
	}

}//namespace Prog3