#pragma once
#include <stack>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <functional>
#include "IMathObject.h"
#include "Factories.h"


class Solver {
public:
	Solver();
	~Solver();
	double solve(const std::string& expression);
private:
	double binary_operator_calcuation(const double num1, const double num2, BinaryOperator& op);
	double solveBackPolish(std::vector<IMathObject*>& v);
	std::vector<IMathObject*> strCheck(const std::string& expression);
	std::vector<IMathObject*> toPolish(std::vector<IMathObject*>& v);
	DoubleNumberFactory* double_factory;
	UnaryOperatorFactory* unary_factory;
	BinaryOperatorFactory* binary_factory;
	BracketFactory* bracket_factory;
	void printAr(std::vector<IMathObject*>& ar);
};



