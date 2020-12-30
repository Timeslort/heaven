#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_
#include <stdexcept>

namespace Prog4{
	template<class MyType>
	class MyVector{
	public:
		MyVector() : sz(0), maxSize(MyVector::QOUTA), array(new MyType[MyVector::QOUTA]) {}
		MyVector(int);
		MyVector(const MyVector&);
		//
		MyVector& operator=(const MyVector&);
		MyType& operator[](int); // l-value
		MyType operator[](int) const; //r-value
		int size() const { return sz; }
		void push_back(const MyType&);
		MyVector& erase(int);
		~MyVector() { delete[] array; }
	private:
		static const int QOUTA = 10;
		int maxSize;
		int sz;
		MyType* array;
	};

	template<class Tp>
	MyVector<Tp>::MyVector(int size) {
		if (size >= 0) {
			sz = size;
			maxSize = size;
			array = new Tp[size];
		}
		else
			throw std::invalid_argument("Incorrect size!");
	}

	template<class T>
	MyVector<T>::MyVector(const MyVector<T>& copy):sz(copy.sz), maxSize(copy.maxSize) {
		array = new T[maxSize];
		for (int i = 0; i < sz; ++i)
			array[i] = copy.array[i];
	}

	template<class T>
	MyVector<T>& MyVector<T>::operator=(const MyVector<T>& eqvl) {
		if (&eqvl != this) {
			sz = eqvl.sz;
			maxSize = eqvl.maxSize;
			delete[] array;
			array = new T[maxSize];
			for (int i = 0; i < sz; i++) {
				array[i] = eqvl.array[i];
			}
		}
		return *this;
	}

	template<class T>
	T& MyVector<T>::operator[](int indx) {
		if(indx >= sz || indx < 0)
			throw::std::out_of_range("Invalid index");
		return array[indx];
	}

	template<class T>
	T MyVector<T>::operator[](int indx) const {
		if (indx >= sz || indx < 0)
			throw::std::out_of_range("Invalid index");
		return array[indx];
	}

	template<class MyType>
	void MyVector<MyType>::push_back(const MyType& el)
	{
		MyType* delarr = array;
		if (maxSize <= sz) {
			array = new MyType[maxSize += MyVector::QOUTA];
			for (int i = 0; i < sz; ++i)
				array[i] = delarr[i];
			delete[] delarr;
		}
		array[sz] = el;
		++sz;
	}

	template<class MyType>
	MyVector<MyType>& MyVector<MyType>::erase(int pos) {
		if (pos >= sz || pos < 0)
			throw::std::out_of_range("Invalid index");	
		for (int i = pos; i < sz; ++i)
			array[i] = array[i + 1];
		--sz;
		return *this;
	}
	
}//prog4
#endif