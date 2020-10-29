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
		int type; // Тип входящая (1)entrance ,выходящая (0)output
		int connection; //количесво связей у клеммы у entrance(0,1), у output(0,1,2,3)
		int signal; // состояние сигнала (0,1,X - неопределнный)
		Klemm(int tip = 0, int conect = 0, int sig = 3): type(tip), connection(conect), signal(sig) {} // по умолчанию тип output(0), кол-во свзяей 0, сигнал X(3)
	};

	class LogicalElement {
	public:
		LogicalElement(int in = 0, int out = 0); // конструктор по умолчанию 0 входящих, 0 выходящих
		LogicalElement(Klemm&, int count); // конструктор с использованием прототипа клеммы и количества втсавок этой копии
		void GetKlemm(void); // вывести клемму с индексом (вводится внутри)
		void GetKlemm(int) const; // вывести клемму с уже готовым индексом
		void GetAllKlemm(void) const; // вывести все клеммы
		int GetNumEntence(void) const { return numEntence; }
		int GetNumOutput(void) const { return numOutput; }
		Klemm GetKlmm(int index) const {
			if (index + 1 > numEntence + numOutput || index < 0)
				throw std::invalid_argument("Incorrect index!!!");
		return array[index];
		}
		void SetKlemm(int num); // изменить клему с номером
		void SetKlemm(int indx, const Klemm&);
		void Redefinition(void); // переназначение всех клемм
		void AddKlemm(void); // добавляение клемм пока не станет 20
		void IncreaseConnection(int indx); // увелечение связей клеммы с индексом (на количесвто вводимое с клавиатуры)
		void DecreaseConnection(int indx); // уменьшение свзяей клеммы с индексом (на количесвто вводимое с клавиатуры)
	private:
		Klemm array[20]; // массив клемм
		int numEntence; // число Входных клемм
		int numOutput; // число Выходных клемм
		Error GetSignal(int &); // корректный ввод сигнала
		Error CurrectChoice(int&, int start, int end); // корректный ввод чилса в диапозоне [start;end]
	};
}