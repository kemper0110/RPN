#pragma once
//#include <typeinfo>
#include "OperatorStatus.h"

__interface IMathObject
{
	virtual size_t type() = 0;
};


class DoubleNumber : public IMathObject
{
public:
	DoubleNumber(double number) : number(number) {}
	~DoubleNumber() {}
	size_t type() {
		return typeid(DoubleNumber).hash_code();
	}
	const double number;
};


class UnaryOperator : public IMathObject
{
public:
	UnaryOperator(Status* status) {
		status_ = status;
	}
	~UnaryOperator() {
		delete status_;
	}
	size_t type() {
		return typeid(UnaryOperator).hash_code();
	}
	size_t toInt() {
		return status_->toInt();
	}
	size_t getPriority() {
		return status_->getPriority();
	}
private:
	Status* status_;
};

class BinaryOperator : public IMathObject
{
public:
	BinaryOperator(Status* status) {
		status_ = status;
	}
	~BinaryOperator() {
		delete status_;
	}
	size_t type() {
		return typeid(BinaryOperator).hash_code();
	}
	size_t toInt() {
		return status_->toInt();
	}
	size_t getPriority() {
		return status_->getPriority();
	}
private:
	Status* status_;
};

class Bracket : public IMathObject
{
public:
	Bracket(Status* status){
		status_ = status;
	}
	~Bracket(){
		delete status_;
	}
	size_t type() {
		return typeid(Bracket).hash_code();
	}
	size_t toInt() {
		return status_->toInt();
	}
	size_t getPriority() {
		return status_->getPriority();
	}
private:
	Status* status_;
};



//class IMathObject
//{
//public:
//	//virtual MathObject();
//	virtual ~IMathObject() {}
//	virtual size_t type() = 0;
//private:
//};