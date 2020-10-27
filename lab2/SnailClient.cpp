#include <iostream>
#include"\Проекты\Программы\StaticSnailLibrary\StaticSnailLibrary\PascalSnail.h"
#define LINE std::cout << "|-------------------------------------------|" << std::endl
#define SMALL_LINE std::cout << "--------------------------------------" << std::endl
//#define DEBUG

enum Error {
	INCORRECT_IN = 1,
	SUCCESS = 0
};

Error getDouble(double&);
Error getInt(int&);

int main()
{
	const char* type[4] = { "with loop", "cardioid", "kinked", "oval" };
	int flag = 1;
	register short i;
#ifdef DEBUG
	double test1;
	Prog2::PascalSnail TestSnail1(12.0, 15.0);
	Prog2::Point testPoint1(5.9, 6.0);
	Prog2::Radius testRad(2.0);

	test1 = TestSnail1.GetA();
	std::cout << "test 1 get a is " << test1 << "in constructor " << 15.0 << std::endl;
	LINE;
	test1 = TestSnail1.GetL();
	std::cout << "test 1 get l is " << test1 << "in constructor " << 12.0 << std::endl;
	LINE;
	std::cout << "test 1 point have coordinates before get x: " << testPoint1.x << " y: " << (&testPoint1)->y << std::endl;
	testPoint1 = TestSnail1.GetCenter();
	std::cout << "test 1 getc center point is x: " << testPoint1.x << " y: " << (&testPoint1)->y << std::endl;
	LINE;
	test1 = 99.99;
	testPoint1.x = 59.2;
	testPoint1.y = 92.8;
	TestSnail1.SetA(test1).SetL(test1).SetCeneter(&testPoint1);
	test1 = TestSnail1.GetA();
	std::cout << "test 1 get a is " << test1 << "in constructor " << 99.99 << std::endl;
	test1 = TestSnail1.GetL();
	std::cout << "test 1 get l is " << test1 << "in constructor " << 99.99 << std::endl;
	testPoint1 = TestSnail1.GetCenter();
	std::cout << "test 1 getc center point is x: " << testPoint1.x << " y: " << (&testPoint1)->y << std::endl;
	LINE;
	TestSnail1.SetLA(45.9, 24.33);
	test1 = TestSnail1.GetA();
	std::cout << "test 1 get a is " << test1 << " in constructor " << 24.33 << std::endl;
	test1 = TestSnail1.GetL();
	std::cout << "test 1 get l is " << test1 << " in constructor " << 45.9 << std::endl;
	LINE;
	testPoint1.x = 129.2;
	testPoint1.y = 1232.8;
	TestSnail1.SetAll(testPoint1, 66.6, 99.9);
	testPoint1.x = 0;
	testPoint1.y = 0;
	testPoint1 = TestSnail1.GetCenter();
	std::cout << "SETALL test 1 getc center point is x: " << testPoint1.x << " y: " << (&testPoint1)->y << std::endl;
	test1 = TestSnail1.GetA();
	std::cout << "test 1 get a is " << test1 << "in constructor " << 45.9 << std::endl;
	test1 = TestSnail1.GetL();
	std::cout << "test 1 get l is " << test1 << "in constructor " << 24.33 << std::endl;
	LINE;
	test1 = TestSnail1.PolarDistance(26.7);
	std::cout << "test 1 PolarDistance is " << test1 << std::endl;
	LINE;
	std::cout << "Radius befor test A " << testRad.radiusA << " C " << testRad.radiusC << " O " << testRad.radiusO << std::endl;
	TestSnail1.RadСurv(testRad);
	std::cout << "Radius after test A " << testRad.radiusA << " C " << testRad.radiusC << " O " << testRad.radiusO << std::endl;
	LINE;
	int testform = TestSnail1.Form();
	std::cout << "Test form is " << type[testform - 1] << std::endl;
	LINE;
	test1 = TestSnail1.PolarArea();
	std::cout << "Polar area is " << test1 << std::endl;
	char* s = nullptr;
	s = TestSnail1.TextForm();
	std::cout << "Text form is " << s << std::endl;
	delete[] s;
#endif
	Prog2::PascalSnail snail;
	Prog2::Radius curvature;
	Prog2::Point center;
	int workForm;
	double workDist, workArea, angle, newX, newY, newA, newL;
	char* textform = nullptr;
	const char* dialog[9] = { "  Enter action number",
							"1.Change center point.", "2.Change \"a\".", "3.Change \"l\".",
							"4.Find out the value of the center coordinates.", "5.Discover \"a\".", "6.Discover \"l\".",
							"7.Make calculations.","0.Quit" };

	LINE;

	std::cout << "Default constructor values is :" << std::endl
		<< "Center coordinate  is : x = " << center.x << " y = " << center.y << std::endl
		<< "Curature radius is : A(" << curvature.radiusA << ") C(" << curvature.radiusC << ") O(" << curvature.radiusO << ")" << std::endl
		<< "Snail values is : \"l\" = " << snail.GetL() << " \"a\" = " << snail.GetA() << std::endl;
	workDist = snail.PolarDistance(75.0);
	snail.RadСurv(curvature);
	workForm = snail.Form();
	workArea = snail.PolarArea();
	textform = snail.TextForm();
	std::wcout << "----------------------------------------" << std::endl;
	std::cout << "  Default values for Pascal snail with constructor parametrs is :" << std::endl
		<< "Distance to center depending on angle (default is 75.0) in polar coordinate is :" << workDist << std::endl
		<< "Radius's of carvoture is : A(" << curvature.radiusA << ") C(" << curvature.radiusC << ") O(" << curvature.radiusO << ")" << std::endl
		<< "Pascal snail have form : " << type[workForm - 1] << std::endl
		<< "Area in polar coordinate is : " << workArea << std::endl
		<< "Text form : " << textform << std::endl;
	delete[] textform;

	while (flag) {
		LINE;
		for (i = 0; i <= 8; i++)
			std::cout << dialog[i] << std::endl;
		while (getInt(flag)) {
			std::cout << "You wrong try again !!!" << std::endl;
			std::cin.clear();
			while (std::cin.get() != '\n');
		}

		switch (flag) {
		case 1:
			center = snail.GetCenter();
			std::cout << "Enter value of new x = ";
			if (getDouble(newX)) {
				std::cout << std::endl << "Incorrect value, x will not be changed!" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}
			else {
				center.x = newX;
				snail.SetCeneter(&center);
			}
			std::cout << std::endl << "Enter value of new y = ";
			if (getDouble(newY)) {
				std::cout << std::endl << "Incorrect value, y will not be changed!" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}
			else {
				center.y = newY;
				snail.SetCeneter(&center);
			}
			std::cout << "Now values is : x = " << center.x << " y = " << center.y << std::endl;
			break;
		case 2:
			std::cout << "Enter new value of \"a\"" << std::endl;
			if (getDouble(newA)) {
				std::cout << "Incorrect value! \"a\" will not be changed." << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}
			else
			{
				try {
					snail.SetA(newA);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
				std::cout << "Now \"a\" is " << snail.GetA() << std::endl;
			}
			break;
		case 3:
			std::cout << "Enter new value of \"l\"" << std::endl;
			if (getDouble(newL)) {
				std::cout << "Incorrect value! \"l\" will not be changed." << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}
			else
			{
				try {
					snail.SetL(newL);
				}
				catch (std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
				std::cout << "Now \"l\" is " << snail.GetL() << std::endl;
			}
			break;
		case 4:
			center = snail.GetCenter();
			std::cout << "Center values are : x = " << center.x << " y = " << center.y << std::endl;
			break;
		case 5:
			std::cout << "Right now \"a\" = " << snail.GetA() << std::endl;
			break;
		case 6:
			std::cout << "Right now \"l\" = " << snail.GetL() << std::endl;
			break;
		case 7:
			SMALL_LINE;
			std::cout << "Enter angle pls :";
			if (getDouble(angle)) {
				std::cout << std::endl << "Incorrect value, can't calculate!!" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n');
			}
			else {
				workDist = snail.PolarDistance(angle);
				std::cout << "Distance with angle " << angle << " is " << workDist << std::endl;
			}
			SMALL_LINE;
			workArea = snail.PolarArea();
			std::cout << "Polar area is " << workArea << std::endl;
			SMALL_LINE;
			workForm = snail.Form();
			std::cout << "Pascal snail type is " << type[workForm - 1] << std::endl;
			SMALL_LINE;
			textform = snail.TextForm();
			std::cout << "The equation is :" << std::endl
				<< "   " << textform << std::endl;
			break;
		}

	}
	LINE;
	return 0;
}

Error getDouble(double& a) {
	std::cin >> a;
	if (!std::cin.good())
		return INCORRECT_IN;
	return SUCCESS;
}

Error getInt(int& a) {
	std::cin >> a;
	if (!std::cin.good() || a > 7 || a < 0) {
		return INCORRECT_IN;
	}
	return SUCCESS;
}
