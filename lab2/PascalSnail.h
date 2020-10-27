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
		double radiusA; //Вершина
		double radiusC; //Вершина
		double radiusO; //Полюс
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
		//get'еры
		double GetA(void) const { return a; };
		double GetL(void) const { return l; };
		Point GetCenter() const { return Center; };
		//set'еры
		PascalSnail& SetA(double);
		PascalSnail& SetL(double);
		PascalSnail& SetCeneter(Point*);
		void SetLA(double setL, double setA);
		void SetAll(const Point&, double setL, double setA);
		//Расстояние до цетра в полярной системе координат в зависимости от угла 
		double PolarDistance(double) const;
		//Радиус кривизны в характерных точках
		void RadСurv(Radius&) const;
		//Тип формы (С петлей, кардиоида, с перегибом, овальная)
		FORM Form(void) const;
		//Площадь описываемую полярным радиусом
		double PolarArea(void) const;
		//Текстовое представление уравнения в декартововой системе координат
		char* TextForm(void) const;
	private:
		Point Center; // центр улитки Паскаля
		double l; //расстояние на которое смещается точка вдоль радиус вектора.
		double a; // диаметр исходной окружности
	};
}
#endif