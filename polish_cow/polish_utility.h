#pragma once
#include <stack>
#include <queue>
#include <map>
#include <string>
#include <chrono>
#include <iostream>


size_t isNumber(char* str_begin, char* str_end, double& num);	
double solveBackPolish(std::string str);
std::string toPolish(std::string str);

double operator_calcuation(double num1, double num2, char op);
bool isOperator(char op);
int getPriority(char op);



size_t isNumber(char* str_begin, char* str_end, double& num) {
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


double solveBackPolish(std::string str) {
	std::stack <double> nums;
	size_t i = 0;
	while (i < str.length()) {
		if (str[i] == ' ') {
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


std::string toPolish(std::string str) {
	std::string out;
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
					throw "end bracket not found or dividor error";
				out += ' ';
				out += signs.top();
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
		signs.pop();
	}
	return out;
}



// GOOD

int getPriority(char op) {
	char operators[7] = { '(', ')', '+', '-', '*', '/', '^' };
	int priority[7] = { 0, 0, 1, 1, 2, 2, 3 };
	for (int i = 0; i < 7; i++)
		if (operators[i] == op)
			return priority[i];
	return -1;
}

bool isOperator(char op) {
	if (op == '-' || op == '+' || op == '*' || op == '/' || op == '^')
		return true;
	return false;
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