#include<iostream>
#include<exception>
#include<string.h>
#include<math.h>
#include<stdio.h>
#include"PascalSnail.h"

namespace Prog2 {

	Radius::Radius(double a, double c, double o) {
		radiusA = a > 0 ? a : 0;
		radiusC = c > 0 ? c : 0;
		radiusO = o > 0 ? o : 0;
	}

	PascalSnail::PascalSnail(double wl, double wa) {
		if (wl <= 0)
			throw std::exception("Invalid parameter l, l set in 1");
		l = wl;
		if (wa <= 0)
			throw std::exception("Invalid parameter a, a set in 1");
		a = wa;
	}

	PascalSnail::PascalSnail(const Point& cntr, double wl, double wa)
		:Center(cntr) {
		if (wl <= 0)
			throw std::exception("Invalid parameter l, l set in 1");
		l = wl;
		if (wa <= 0)
			throw std::exception("Invalid parameter a, a set in 1");
		a = wa;
	}
	/* set'еры */

	PascalSnail& PascalSnail::SetA(double setA) {
		if (setA <= 0)
			throw std::exception("Invalid value, cant set!");
		a = setA;
		return *this;
	}

	PascalSnail& PascalSnail::SetL(double SetL) {
		if (SetL <= 0)
			throw std::exception("Invalid value, cant set!");
		l = SetL;
		return *this;
	}

	PascalSnail& PascalSnail::SetCeneter(Point* cntrPtr) {
		Center = *cntrPtr;
		return *this;
	}

	void PascalSnail::SetLA(double SetL, double SetA) {
		if (SetL <= 0)
			throw std::exception("Invalid value l, cant set it!");
		l = SetL;
		if (SetA <= 0)
			throw std::exception("Invalid value a, cant set it!");
		a = SetA;
	}

	void PascalSnail::SetAll(const Point& cntr, double setL, double setA)
	{
		Center = cntr;
		if (setL <= 0)
			throw std::exception("Invalid value l, cant set it!");
		l = setL;
		if (setA <= 0)
			throw std::exception("Invalid value a, cant set it!");
		a = setA;
	}
	/* Элементы - функции (методы) */
	double PascalSnail::PolarDistance(double angle) const {
		double distance, cosAngle = cos(angle);
		distance = a * cosAngle + l;
		return distance >= 0 ? distance : -distance;
	}

	FORM PascalSnail::Form(void) const {
		int form;
		if (l / a < 1)
			return WITH_LOOP;
		if (l / a == 1)
			return CARDIOID;
		if (l / a > 1 && l / a < 2)
			return KINKED;
		if (l / a >= 2)
			return OVAL;
	}

	double PascalSnail::PolarArea(void) const {
		int form = Form();
		double area;

		switch (form) {
		case WITH_LOOP:
			area = (0.5 * a * a + l * l) * (acos(-l / a) + acos(l / a));
			break;
		case CARDIOID:
			area = 3.0 / 2.0 * PI * a * a;
			break;
		case KINKED:case OVAL:
			area = (0.5 * a * a + l * l) * PI;
			break;
		}
		return area;
	}

	char* PascalSnail::TextForm(void) const {
		const char* text = "((x  -  )^2 + (y  -  )^2 + (y  -  ))^2 = ((x  -  )^2 + (y  -  )^2)       ";
		int l = strlen(text) + 1;
		char num[20];
		sprintf_s(num, 20, "%.2f", Center.x);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", Center.y);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", PascalSnail::l * PascalSnail::l);
		l += strlen(num);
		sprintf_s(num, 20, "%.2f", PascalSnail::a);
		char* textForm = new char[l];
		if (Center.x == 0)
			sprintf_s(textForm, l, "(x^2");
		else
			sprintf_s(textForm, l, "((x%+.2f)^2 ", Center.x);
		int k = strlen(textForm);
		if (Center.y == 0) {
			sprintf_s(textForm + k, l - k, " + y^2");
			k = strlen(textForm);
			sprintf_s(textForm + k, l - k, "%+.2f*y)^2 = ", a);
		}
		else {
			sprintf_s(textForm + k, l - k, "+ (y%+.2f)^2", Center.y);
			k = strlen(textForm);
			sprintf_s(textForm + k, l - k, "%+.2f*(y%+.2f))^2 = ", a, Center.y);
		}
		k = strlen(textForm);
		if (Center.x == 0)
			sprintf_s(textForm + k, l - k, "%.2f * (x^2 + ", PascalSnail::l * PascalSnail::l);
		else
			sprintf_s(textForm + k, l - k, "%.2f * ((x%+.2f)^2 + ", PascalSnail::l, Center.x);
		k = strlen(textForm);
		if (Center.y == 0)
			sprintf_s(textForm + k, l - k, "y^2)");
		else
			sprintf_s(textForm + k, l - k, "(y%+.2f)^2)", Center.y);

		return textForm;
	}

	void PascalSnail::RadСurv(Radius& rad) const {
		if (l == a) {
			rad.radiusA = 4.0 / 3.0 * a;
			rad.radiusC = 0;
			rad.radiusO = 0;
		}
		if (l < a) {
			rad.radiusA = (l + a) * (l + a) / (l + 2 * a);
			rad.radiusC = (l - a) * (l - a) / abs(l - 2 * a);
			rad.radiusO = 0.5 * pow((a * a - l * l), 0.5);
		}
		if (l > a && l != 2 * a)
			rad.radiusA = (l + a) * (l + a) / (l + 2 * a);
		rad.radiusC = (l - a) * (l - a) / abs(l - 2 * a);
		rad.radiusO = 0; //обособленна от улитки
		if (l == 2 * a) {
			rad.radiusA = (l + a) * (l + a) / (l + 2 * a);
			rad.radiusC = 0; //обособленна от улитки
			rad.radiusO = 0; //обособленна от улитки
		}
	}
}