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
		int type; // ��� �������� (1)entrance ,��������� (0)output
		int connection; //��������� ������ � ������ � entrance(0,1), � output(0,1,2,3)
		int signal; // ��������� ������� (0,1,X - �������������)
		Klemm(int tip = 0, int conect = 0, int sig = 3): type(tip), connection(conect), signal(sig) {} // �� ��������� ��� output(0), ���-�� ������ 0, ������ X(3)
	};

	class LogicalElement {
	public:
		LogicalElement(int in = 0, int out = 0); // ����������� �� ��������� 0 ��������, 0 ���������
		LogicalElement(Klemm&, int count); // ����������� � �������������� ��������� ������ � ���������� ������� ���� �����
		void GetKlemm(void); // ������� ������ � �������� (�������� ������)
		void GetKlemm(int) const; // ������� ������ � ��� ������� ��������
		void GetAllKlemm(void) const; // ������� ��� ������
		int GetNumEntence(void) const { return numEntence; }
		int GetNumOutput(void) const { return numOutput; }
		Klemm GetKlmm(int index) const {
			if (index + 1 > numEntence + numOutput || index < 0)
				throw std::invalid_argument("Incorrect index!!!");
		return array[index];
		}
		void SetKlemm(int num); // �������� ����� � �������
		void SetKlemm(int indx, const Klemm&);
		void Redefinition(void); // �������������� ���� �����
		void AddKlemm(void); // ����������� ����� ���� �� ������ 20
		void IncreaseConnection(int indx); // ���������� ������ ������ � �������� (�� ���������� �������� � ����������)
		void DecreaseConnection(int indx); // ���������� ������ ������ � �������� (�� ���������� �������� � ����������)
	private:
		Klemm array[20]; // ������ �����
		int numEntence; // ����� ������� �����
		int numOutput; // ����� �������� �����
		Error GetSignal(int &); // ���������� ���� �������
		Error CurrectChoice(int&, int start, int end); // ���������� ���� ����� � ��������� [start;end]
	};
}