#pragma once
#include "IMathObject.h"



class DoubleNumberFactory
{
public:
	IMathObject* createMathObject(double num) {
		return (IMathObject*)new DoubleNumber{ num };
	}
};

class UnaryOperatorFactory
{
public:
	IMathObject* createMathObject(Status *status) {
		return (IMathObject*)new UnaryOperator{ status };
	}
};

class BinaryOperatorFactory
{
public:
	IMathObject* createMathObject(Status* status) {
		return (IMathObject*)new BinaryOperator{ status };
	}
};

class BracketFactory
{
public:
	IMathObject* createMathObject(Status* status) {
		return (IMathObject*)new Bracket{ status };
	}
};