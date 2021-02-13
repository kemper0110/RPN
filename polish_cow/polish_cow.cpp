#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <chrono>
//#include "RPN.h"
//#include "stack"
//#include "math.h"
bool isOperator(std::string, char&);
bool isOperator(char);
double solveBackPolish(std::string);
double operator_calcuation(double, double, char);



bool isHigherPriority(char op1, char op2) {
	// TODO: blocking search
	char operators[7] = { '(', ')', '+', '-', '*', '/', '^' };
	int priority[7] = { 0, 0, 1, 1, 2, 2, 3 };

	int pos1, pos2;
	for (int i = 0; i < 7; i++) {
		if (operators[i] == op1)
			pos1 = i;
		if (operators[i] == op2)
			pos2 = i;
	}

	return priority[pos1] >= priority[pos2];  // maybe '>'
}

int isNumber(std::string str, double& num) {
	num = 0;

	bool pastPoint = false;
	int afterPoint = 0;

	auto fromChar = [](char c) { return c - '0'; };
	int afterLastD;
	for (afterLastD = 0; afterLastD < str.length() && (str[afterLastD] >= '0' && str[afterLastD] <= '9' || str[afterLastD] == '.'); afterLastD++)
	{
		if (str[afterLastD] == '.') {
			pastPoint = true;
			continue;
		}

		num += fromChar(str[afterLastD]);
		num *= 10;
		if (pastPoint)
			afterPoint++;
	}
	num /= 10;
	for (int i = 0; i < afterPoint; i++)
		num /= 10;


	return afterLastD;
}



std::string toPolish(std::string str) {
	std::string out;
	std::stack <char> signs;

	int i = 0;
	// Пока есть ещё символы для чтения:
	while (!str.empty() && i < str.length()) {

		// Читаем очередной символ.
		char c = str[i];

		// Пропускаем пробелы без остальных проверок
		if (c == ' ') {
			i++;
			continue;
		}

		// Если символ является числом, добавляем его к выходной строке.
		double num;
		int len = isNumber(str.substr(i), num);
		if (len > 0) {
			out += ' ';
			out += std::to_string(num);
			i += len;
			continue;
		}

		// Если символ является открывающей скобкой, помещаем его в стек.
		if (c == '(') {
			signs.push('(');
		}
		// Если символ является закрывающей скобкой:
		if (c == ')') {
			// До тех пор, пока верхним элементом стека не станет открывающая скобка, 
			// выталкиваем элементы из стека в выходную строку.
			// При этом открывающая скобка удаляется из стека, но в выходную строку не добавляется. 
			// Если стек закончился раньше, чем мы встретили открывающую скобку, 
			// это означает, что в выражении либо неверно поставлен разделитель, либо не согласованы скобки.
			while (signs.top() != '(') {
				if (signs.empty())
					throw "end bracket not found or dividor error";
				out += ' ';
				out += signs.top();
				signs.pop();
			}
			signs.pop();
		}

		// Если символ является бинарной операцией о1, тогда:
		if (isOperator(c)) {
			//	1) TODO: пока на вершине стека префиксная функция…
			//			… ИЛИ операция на вершине стека приоритетнее o1   
			//	   TODO:… ИЛИ операция на вершине стека левоассоциативная с приоритетом как у o1
			//	   … выталкиваем верхний элемент стека в выходную строку;
			while (!signs.empty() && isHigherPriority(signs.top(), c)) {
				out += ' ';
				out += signs.top();
				signs.pop();
			}
			//	2) помещаем операцию o1 в стек.
			signs.push(c);
		}
		i++;
	}

	while (!signs.empty()) {
		out += ' ';
		out += signs.top();
		signs.pop();
	}
	return out;
}



int main()
{
	std::cout.precision(5);
	std::string str0 = "1+2*(3+4/2-(1+2))*2+1";
	std::string str = "5*(3+4/2-(1+2))*2+1";

	//std::string str_backpolish = "8 2 5 * + 1 3 2 * + 4 - / ";


	//std::cin >> str;
	//double ans = solveBackPolish(str_backpolish);
	//std::cout << ans;

	std::string expr1 = "1 + 2 * 3";
	std::string expr2 = "( (3 + 7) * 9 - 2 / 2 + 9 * 1 + 1) / ( 1 + 6 / 2 - 1 + 6 / (2 - 1) )";


	auto start = std::chrono::steady_clock::now();
	std::string expr = expr2;
	std::string polish = toPolish(expr);
	double answer = solveBackPolish(polish);
	std::cout << "input expression: " << expr << std::endl;
	std::cout << "polish notation: " << polish << std::endl;
	std::cout << "answer: " << answer << std::endl;
	auto stop = std::chrono::steady_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
}



















bool isOperator(std::string str, char& op) {
	op = str[0];
	if (op == '-' || op == '+' || op == '*' || op == '/' || op == '^')
		return true;
	return false;
}
bool isOperator(char op) {
	if (op == '-' || op == '+' || op == '*' || op == '/' || op == '^')
		return true;
	return false;
}



double solveBackPolish(std::string str) {
	std::stack <double> nums;
	while (!str.empty()) {
		double num;
		int len = isNumber(str, num);
		if (str[0] == ' ') {
			str = str.substr(1);
		}
		if (len > 0) {
			nums.push(num);
			str = str.substr(len);
			continue;
		}
		char op;
		if (isOperator(str, op)) {
			double right = nums.top(); nums.pop();
			double left = nums.top(); nums.pop();
			double ans = operator_calcuation(left, right, op);
			nums.push(ans);
			str = str.substr(1);
		}
	}
	return nums.top();
}

double operator_calcuation(double num1, double num2, char op) {
	switch (op)
	{
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	case '^':
		return std::pow(num1, num2);
	}
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