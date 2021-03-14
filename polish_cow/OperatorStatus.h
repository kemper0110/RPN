#pragma once

__interface Status
{
	virtual size_t toInt() = 0;
	virtual size_t getPriority() = 0;
};


class OpenBracket : public Status {
public:
	OpenBracket(){}
	~OpenBracket(){}
	const static size_t Int = 1;
	const static size_t priority = 0;
	size_t toInt() {
		return 1;
	}
	size_t getPriority() {
		return 0;
	}
};

class CloseBracket : public Status {
public:
	CloseBracket() {}
	~CloseBracket() {}
	const static size_t Int = 2;
	const static size_t priority = 0;
	size_t toInt() {
		return 2;
	}
	size_t getPriority() {
		return 0;
	}
};


class Plus : public Status
{
public:
	Plus(){}
	~Plus(){}
	const static size_t Int = 3;
	const static size_t priority = 1;
	size_t toInt() {
		return 3;
	}
	size_t getPriority() {
		return 1;
	}
};

class Minus : public Status
{
public:
	Minus(){}
	~Minus(){}
	const static size_t Int = 4;
	const static size_t priority = 1;
	size_t toInt() {
		return 4;
	}
	size_t getPriority() {
		return 1;
	}
};

class Mul : public Status
{
public:
	Mul() {}
	~Mul() {}
	const static size_t Int = 5;
	const static size_t priority = 2;
	size_t toInt() {
		return 5;
	}
	size_t getPriority() {
		return 2;
	}
};

class Div : public Status
{
public:
	Div() {}
	~Div() {}
	const static size_t Int = 6;
	const static size_t priority = 2;
	size_t toInt() {
		return 6;
	}
	size_t getPriority() {
		return 2;
	}
};

class Pow : public Status
{
public:
	Pow() {}
	~Pow() {}
	const static size_t Int = 8;
	const static size_t priority = 3;
	size_t toInt() {
		return 7;
	}
	size_t getPriority() {
		return 3;
	}
};