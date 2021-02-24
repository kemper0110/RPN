#pragma once
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <iostream>


size_t isNumber(const char* str_begin, const char* str_end, double& num);
double solveBackPolish(const std::string str);
std::string toPolish(const std::string str);

double operator_calcuation(const double num1, const double num2, const char op);
bool isOperator(const char op);
int getPriority(const char op);



size_t isNumber(const char* str_begin, const char* str_end, double& num) {
	num = 0;
	bool pastPoint = false;
	size_t afterPoint = 0;
	auto fromChar = [](char c) { return c - '0'; };
	size_t afterLastD;
	for (afterLastD = 0; str_begin + afterLastD < str_end && (str_begin[afterLastD] >= '0' && str_begin[afterLastD] <= '9' || str_begin[afterLastD] == '.'); afterLastD++) {
		if (str_begin[afterLastD] == '.') {
			pastPoint = true;
			continue;
		}
		num *= 10;
		num += fromChar(str_begin[afterLastD]);
		if (pastPoint)
			afterPoint++;
	}
	for (size_t i = 0; i < afterPoint; i++)
		num /= 10;
	return afterLastD;
}


double solveBackPolish(const std::string str) {
	std::stack <double> nums;
	size_t i = 0;
	while (i < str.length()) {
		if (str[i] == ' ' || str[i] == 0) {
			i++;
			continue;
		}
		double num;
		int len = isNumber(&str[i], &str[str.length()], num);
		if (len > 0) {
			nums.push(num);
			i += len;
			continue;
		}
		if (isOperator(str[i])) {
			double right = nums.top(); nums.pop();
			double left = nums.top(); nums.pop();
			double ans = operator_calcuation(left, right, str[i]);
			nums.push(ans);
			i++;
		}
	}
	return nums.top();
}


std::string toPolish(const std::string str) {
	//std::queue <char> out;
	std::string out;
	//out.reserve(str.length() * 3 / 2);  // 998
	// without // 947 // 42
	//out.reserve(str.length() * 5 / 4); // 963
	out.reserve(str.length()); //  932
	std::stack <char> signs;

	size_t i = 0;
	// ���� ���� ��� ������� ��� ������:
	while (i < str.length()) {
		// ������ ��������� ������.
		char c = str[i];
		// ���������� ������� ��� ��������� ��������
		if (c == ' ') {
			i++;
			continue;
		}
		// ���� ������ �������� ������, ��������� ��� � �������� ������.
		double num;
		int len = isNumber(&str[i], &str[str.length()], num);
		if (len > 0) {
			out += ' ';
			out += std::to_string(num);
			//out.push(' ');
			//std::string str_num = std::to_string(num);
			//for (int i = 0; i < str_num.length(); i++)
			//	out.push(str_num[i]);
			i += len;
			continue;
		}
		// ���� ������ �������� ����������� �������, �������� ��� � ����.
		if (c == '(') {
			signs.push('(');
		}
		// ���� ������ �������� ����������� �������:
		if (c == ')') {
			// �� ��� ���, ���� ������� ��������� ����� �� ������ ����������� ������, 
			// ����������� �������� �� ����� � �������� ������.
			// ��� ���� ����������� ������ ��������� �� �����, �� � �������� ������ �� �����������. 
			// ���� ���� ���������� ������, ��� �� ��������� ����������� ������, 
			// ��� ��������, ��� � ��������� ���� ������� ��������� �����������, ���� �� ����������� ������.
			while (signs.top() != '(') {
				if (signs.empty())
					throw "end bracket not found or separator error";
				out += ' ';
				out += signs.top();
				//out.push(' ');
				//out.push(signs.top());
				signs.pop();
			}
			signs.pop();
		}
		// ���� ������ �������� �������� ��������� �1, �����:
		if (isOperator(c)) {
			//	1) TODO: ���� �� ������� ����� ���������� ��������
			//			� ��� �������� �� ������� ����� ������������ o1   
			//	   TODO:� ��� �������� �� ������� ����� ����������������� � ����������� ��� � o1
			//	   � ����������� ������� ������� ����� � �������� ������;
			while ( !signs.empty() && getPriority(signs.top()) >= getPriority(c) ) {
				out += ' ';
				out += signs.top();
				//out.push(' ');
				//out.push(signs.top());
				signs.pop();
			}
			//	2) �������� �������� o1 � ����.
			signs.push(c);
		}
		i++;
	}
	while (!signs.empty()) {
		out += ' ';
		out += signs.top();
		//out.push(' ');
		//out.push(signs.top());
		signs.pop();
	}
	/*std::string out_str;
	out_str.resize(out.size());
	while (!out.empty()) {
		out_str += out.front();
		out.pop();
	}
	return out_str;*/
	//std::cout << "size: " << out.length() << std::endl;
	return out;
}



// GOOD

int getPriority(const char op) {
	constexpr char operators[7] = { '(', ')', '+', '-', '*', '/', '^' };
	constexpr int priority[7] = { 0, 0, 1, 1, 2, 2, 3 };
	for (int i = 0; i < 7; i++)
		if (operators[i] == op)
			return priority[i];
	return -1;
}

bool isOperator(const char op) {
	if (op == '-' || op == '+' || op == '*' || op == '/' || op == '^')
		return true;
	return false;
}


double operator_calcuation(const double num1, const double num2, const char op) {
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