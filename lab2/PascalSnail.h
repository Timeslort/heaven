#pragma once
#ifndef PascalSnail_H
#define PascalSnaik_H

const float PI = 3.14159;

namespace Prog2 {
	enum FORM {
		WITH_LOOP = 1,
		CARDIOID,
		KINKED,
		OVAL
	};

	struct Radius {
		double radiusA; //�������
		double radiusC; //�������
		double radiusO; //�����
		Radius(double a = 0.0, double b = 0.0, double c = 0.0);
	};

	struct Point {
		double x;
		double y;
		Point(double x0 = 0.0, double y0 = 0.0)
			:x(x0), y(y0) {};
	};

	class PascalSnail {
	public:
		PascalSnail(const Point& cntr, double wl = 1.0, double wa = 1.0);
		PascalSnail(double wl = 1.0, double wa = 1.0);
		//get'���
		double GetA(void) const { return a; };
		double GetL(void) const { return l; };
		Point GetCenter() const { return Center; };
		//set'���
		PascalSnail& SetA(double);
		PascalSnail& SetL(double);
		PascalSnail& SetCeneter(Point*);
		void SetLA(double setL, double setA);
		void SetAll(const Point&, double setL, double setA);
		//���������� �� ����� � �������� ������� ��������� � ����������� �� ���� 
		double PolarDistance(double) const;
		//������ �������� � ����������� ������
		void Rad�urv(Radius&) const;
		//��� ����� (� ������, ���������, � ���������, ��������)
		FORM Form(void) const;
		//������� ����������� �������� ��������
		double PolarArea(void) const;
		//��������� ������������� ��������� � ������������ ������� ���������
		char* TextForm(void) const;
	private:
		Point Center; // ����� ������ �������
		double l; //���������� �� ������� ��������� ����� ����� ������ �������.
		double a; // ������� �������� ����������
	};
}
#endif