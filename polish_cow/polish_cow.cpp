#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <chrono>
#include <Windows.h>
#include "stack"
#include "polish_utility.h"

long long perfomance_test(const std::string expr, const int count);
void 🧠();
void 🐔();
void 🐣();
void 👣();

int main()
{
	std::cout.precision(5);
	const std::string expr1 = "( (3 + 7) * 9 - 2 / 2 + 9 * 1 + 2 ^ 3 + 2) / ( 1 + 6 / 2 - 1 + 6 / (2 - 1) ) "; // = 108 / 9 = 12

	//perfomance_test(expr1, 3000);
	std::cout << solveBackPolish( toPolish(expr1) );

}

long long perfomance_test(const std::string expr, const int count) {
	// PERFOMANCE TEST
	Sleep(500);
	const int size = 10;
	int time[size];

	for (int j = 0; j < size; j++) {
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < count; i++) {
			std::string polish = toPolish(expr);
			double answer = solveBackPolish(polish);
		}
		auto stop = std::chrono::steady_clock::now();
		time[j] = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
		std::cout << time[j] << std::endl;
	}
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += time[i];
	std::cout << "average = " << (float)sum / size << std::endl;
	// PERFOMANCE TEST

	// expr = "( (3 + 7) * 9 - 2 / 2 + 9 * 1 + 2 ^ 3 + 2) / ( 1 + 6 / 2 - 1 + 6 / (2 - 1) )"
	// count = 3k
	// string.substr() 2347
	// string::iterator  3763
	// char* 914
	return sum / size;
}


//
//double func1arg_calculation(double num, dl::math_funcs func) {
//	// TODO: normal PI
//	const double PI = 3.14;
//	const double PI_2 = PI / 2;
//	switch (func)
//	{
//	case dl::math_funcs::Sin:
//		return std::sin(num);
//	case dl::math_funcs::Cos:
//		return std::cos(num);
//	case dl::math_funcs::Tg:
//		return std::tan(num);
//	case dl::math_funcs::Ctg:
//		return 1. / std::tan(num);
//	case dl::math_funcs::Arcsin:
//		return std::asin(num);
//	case dl::math_funcs::Arccos:
//		return std::acos(num);
//	case dl::math_funcs::Arctg:
//		return std::atan(num);
//	case dl::math_funcs::Arcctg:
//		return PI_2 - std::atan(num);
//	}
//}



//bool isFunc1arg(std::string str, dl::math_funcs& func) {
//	// Sin, Cos, Tg, Ctg, Arcsin, Arccos, Arctg, Arcctg
//	switch (str[0]) {
//	case 's': // sin
//		if (str[1] == 'i' && str[2] == 'n') {
//			func = dl::math_funcs::Sin;
//			return true;
//		}
//		throw "bad sin func";
//	//case 'c': // cos, ctg(cotan)
//	//	if (str[1] == 'o' && str[2] == 's') {
//	//		func = dl::math_funcs::Cos;
//	//		return true;
//	//	}
//	//	if (str[1] == 't' && str[2] == 'g' || str[1] == 'o' && str[2] == 't' && str[3] == 'a' && str[4] == 'n') {
//	//		func = dl::math_funcs::Ctg;
//	//		return true;
//	//	}
//	//	return false;
//	//case 't':
//
//	//	if (str[1] == 'g' || str[1] == 'a' && str[2] == 'n') {
//	//		func = dl::math_funcs::Tg;
//	//		return true;
//	//	}
//	//	return false;
//	//case 'a':
//	//	return true;
//	default:
//		return false;
//	}
//	return false;
//}