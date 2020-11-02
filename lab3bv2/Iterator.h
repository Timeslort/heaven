#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include"Klemm.h"

namespace Prog3 {

	class ConstLogicElementIt {
	public:
		ConstLogicElementIt(Klemm* obj) :cur(obj) {}
		ConstLogicElementIt() :cur(nullptr) {}
		const Klemm& operator *() const;
		ConstLogicElementIt& operator++();
		ConstLogicElementIt operator++(int);
		int operator!=(const ConstLogicElementIt&)const;
		int operator==(const ConstLogicElementIt&)const;
	private:
		Klemm* cur;
	};

}//namespace Prog3
#endif