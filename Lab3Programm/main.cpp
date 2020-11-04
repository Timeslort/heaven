#include<iostream>
#include"bigint.h"
#include<string.h>

int CorrectString(char* str, const char* eqvl); 
int GetInt(int& a);

int main() {
	Prog3b::BigInt a, b;
	const char* dialog[] = {"1.Redefenition A.", "2.Redefinition B.", "3.Increase A.", "4.Increase B.", "5.Decrease A.", "6.Decrease B.",
							"7.Set one digit of number A.", "8.Set one digit of number B."};
	int flag = 1, correctFlag = 1, choice, number; 
	char digit;
	char answer[4];

	while (flag) {
		std::cout << "Enter A : ";
		std::cin >> a;
		std::cout << "Enter B : ";
		std::cin >> b;
		while (correctFlag) {
			std::cout << "-------Is everything ok ?(Yes, No)--------" << std::endl
				<< std::endl << "\t" << "A = " << a << std::endl
				<< "\t" << "B = " << b << std::endl;
			std::cout << "Your answer : ";
			std::cin >> answer;
			std::cin.good();
			while (std::cin.get() != '\n');
			if (CorrectString(answer, "yes"))
				correctFlag = 0;
			else if (CorrectString(answer, "no")) {
				for (int i = 0; i < 8; i++)
					std::cout << dialog[i] << std::endl;
				std::cout << "Enter number of action : ";
				while (GetInt(choice) || choice > 8 || choice < 0)
					std::cout << "Incorrect value!!" << std::endl;
				switch (choice) {
				case 1:
					std::cin.good();
					while (std::cin.get() != '\n');
					std::cout << "Enter A : ";
					std::cin >> a;
					break;
				case 2:
					std::cin.good();
					while (std::cin.get() != '\n');
					std::cout << "Enter B : ";
					std::cin >> b;
					break;
				case 3:
					a.increase();
					break;
				case 4:
					b.increase();
					break;
				case 5:
					a.decrease();
					break;
				case 6:
					b.decrease();
					break;
				case 7:
					std::cout << "Enter number of digit to set : ";
					while (GetInt(number) || number > a.getCount() || number < 1)
						std::cout << "Incorrect number!" << std::endl;
					std::cout << "Enter digit to set : ";
					std::cin >> digit;
					std::cin.good();
					while (std::cin.get() != '\n');
					while (digit > '9' || digit < '0') {
						std::cout << "Incorrect digit!" << std::endl;
						std::cin >> digit;
						std::cin.good();
						while (std::cin.get() != '\n');
					}
					a.setDigit(a.getCount() - number, digit);
					break;
				case 8:
					std::cout << "Enter number of digit to set : ";
					while (GetInt(number) || number > b.getCount() || number < 1)
						std::cout << "Incorrect number!" << std::endl;
					std::cout << "Enter digit to set : ";
					std::cin >> digit;
					std::cin.good();
					while (std::cin.get() != '\n');
					while (digit > '9' || digit < '0') {
						std::cout << "Incorrect digit!" << std::endl;
						std::cin >> digit;
						std::cin.good();
						while (std::cin.get() != '\n');
					}
					b.setDigit(b.getCount() - number, digit);
					break;
				}//switch
			}//answer no
		}//correctFlag
		correctFlag = 1;
		std::cout << '\t' << "A + B = " << a + b << std::endl <<
					'\t' << "A - B = " << a - b << std::endl;
		std::cout << "Did you want to continue ?(Yes, No)" << std::endl <<
			"Your answer : ";
		std::cin >> answer;
		std::cin.good();
		while (std::cin.get() != '\n');
		if (CorrectString(answer, "no"))
			flag = 0;
	}
	return 0;
}

int CorrectString(char* str, const char* eqvl) {
	for (int i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
	if (!strcmp(str, eqvl))
		return 1;
	return 0;
}

int GetInt(int& a) {
	std::cin >> a;
	if (!std::cin.good()) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		return 1;
	}
	std::cin.clear();
	while (std::cin.get() != '\n');
	return 0;
}