#include "polish_utility.h"
#include <iostream>

Solver::Solver() {
	double_factory	= new DoubleNumberFactory;
	unary_factory	= new UnaryOperatorFactory;
	binary_factory	= new BinaryOperatorFactory;
	bracket_factory = new BracketFactory;
}

Solver::~Solver() {
	delete double_factory;
	delete unary_factory;
	delete binary_factory;
	delete bracket_factory;
}

double Solver::solve(const std::string &expression) {
	auto ch = strCheck(expression);
	printAr(ch);
	auto pol = toPolish(ch);
	printAr(pol);
	auto ans = solveBackPolish(pol);
	return ans;
	//return solveBackPolish(toPolish(strCheck(expression)));
}

std::vector<IMathObject*> Solver::strCheck(const std::string& expression) {
	//DoubleNumberFactory*	 double_factory	= new DoubleNumberFactory;
	//UnaryOperatorFactory*	 unary_factory	= new UnaryOperatorFactory;
	//BinaryOperatorFactory* binary_factory = new BinaryOperatorFactory;
	//BracketFactory*		 bracket_factory		= new BracketFactory;
	//std::unique_ptr<DoubleNumberFactory> double_factory(new DoubleNumberFactory);
	//std::unique_ptr<UnaryOperatorFactory> unary_factory(new UnaryOperatorFactory);
	//std::unique_ptr<BinaryOperatorFactory> binary_factory(new BinaryOperatorFactory);
	//std::unique_ptr<BracketFactory> bracket_factory(new BracketFactory);
	std::vector<IMathObject*> expression_array;

	std::stringstream expression_stream(expression);
	char x;
	while (expression_stream >> x) {
		if (x >= '0' && x <= '9') {
			double num;
			expression_stream.putback(x);
			expression_stream >> num;
			expression_array.push_back(double_factory->createMathObject(num));
		}
		if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^') {
			Status* op = nullptr;
			switch (x) {
			case '+': op = (Status*) new Plus; break;
			case '-': op = (Status*) new Minus; break;
			case '*': op = (Status*) new Mul; break;
			case '/': op = (Status*) new Div; break;
			case '^': op = (Status*) new Pow; break;
			}
			expression_array.push_back(binary_factory->createMathObject(op));
		}
		if (x == '(') 
			expression_array.push_back(bracket_factory->createMathObject((Status*)new OpenBracket));
		if (x == ')') 
			expression_array.push_back(bracket_factory->createMathObject((Status*)new CloseBracket));
	}
	return expression_array;
}


double Solver::solveBackPolish(std::vector<IMathObject*>& v) {
	std::stack <double> nums;

	for (size_t i = 0; i < v.size(); i++) {
		size_t type = v[i]->type();

		if (type == typeid(DoubleNumber).hash_code()) {
			auto* num = (DoubleNumber*)v[i];
			nums.push(num->number);
			continue;
		}
		if (type == typeid(BinaryOperator).hash_code()) {
			auto* op = (BinaryOperator*)v[i];
			double right = nums.top(); nums.pop();
			double left = nums.top(); nums.pop();
			double ans = binary_operator_calcuation(left, right, *op);
			nums.push(ans);
			continue;
		}
		if (type == typeid(UnaryOperator).hash_code()) {
			throw "nigga";
		}
	}
	for (int i = 0; i < v.size(); i++)
		delete v[i];
	v.clear();

	return nums.top();
}


std::vector<IMathObject*> Solver::toPolish(std::vector<IMathObject*>& v) {
	std::vector<IMathObject*> out;
	std::stack <IMathObject*> signs;
	// Пока есть ещё символы для чтения:
	for (size_t i = 0; i < v.size(); i++) {
		// Читаем очередной символ.
		size_t type = v[i]->type();
		// Если символ является числом, добавляем его к выходной строке.
		if (type == typeid(DoubleNumber).hash_code()) {
			out.push_back((DoubleNumber*)v[i]);
			continue;
		}
		if (type == typeid(Bracket).hash_code()) {
			// Если символ является открывающей скобкой, помещаем его в стек.
			Bracket* br = (Bracket*)v[i];
			if (br->toInt() == OpenBracket::Int) {
				signs.push(br);
			}
			// Если символ является закрывающей скобкой:
			if (br->toInt() == CloseBracket::Int) {
				// До тех пор, пока верхним элементом стека не станет открывающая скобка, 
				// выталкиваем элементы из стека в выходную строку.
				// При этом открывающая скобка удаляется из стека, но в выходную строку не добавляется. 
				// Если стек закончился раньше, чем мы встретили открывающую скобку, 
				// это означает, что в выражении либо неверно поставлен разделитель, либо не согласованы скобки.
				//while (signs.top() != '(') {
				while (
					// пока скобка, но не открывающаяся?
					(signs.top()->type() == typeid(Bracket).hash_code() && ((Bracket*)signs.top())->toInt() != OpenBracket::Int)
					// или пока это не скобка
					|| signs.top()->type() != typeid(Bracket).hash_code()
					) {
					if (signs.empty())
						throw "end bracket not found or separator error";
					out.push_back(signs.top());
					signs.pop();
				}
				signs.pop();
			}
		}

		// Если символ является бинарной операцией о1, тогда:
		if (type == typeid(BinaryOperator).hash_code()) {
			//	1) TODO: пока на вершине стека префиксная функция…
			//			… ИЛИ операция на вершине стека приоритетнее o1   
			//	   TODO:… ИЛИ операция на вершине стека левоассоциативная с приоритетом как у o1
			//	   … выталкиваем верхний элемент стека в выходную строку;
			while (!signs.empty() &&
				((BinaryOperator*)signs.top())->getPriority() >= ((BinaryOperator*)v[i])->getPriority()) {
				out.push_back(signs.top());
				signs.pop();
			}
			//	2) помещаем операцию o1 в стек.
			signs.push(v[i]);
		}
	}
	while (!signs.empty()) {
		out.push_back(signs.top());
		signs.pop();
	}
	/*for (int i = 0; i < v.size(); i++)
		delete v[i];
	v.clear();*/
	return out;
}

double Solver::binary_operator_calcuation(const double num1, const double num2, BinaryOperator& op) {
	static const auto m_plus = [](double a, double b) -> double		{		return a + b;		};
	static const auto m_minus= [](double a, double b) -> double		{		return a - b;		};
	static const auto m_mul  = [](double a, double b) -> double		{		return a * b;		};
	static const auto m_div  = [](double a, double b) -> double		{		return a / b;		};
	static const auto m_pow  = [](double a, double b) -> double		{	 return std::pow(a, b); };
	//static const std::map <char, std::function<double(double, double)>> mp{
	//	{ '+', m_plus }, { '-', m_minus }, { '*', m_mul }, { '/', m_div }, { '^', m_pow }
	//};
	//return mp.at(op)(num1, num2);
	std::function<double(double, double)> calc[]{
		nullptr, nullptr, nullptr, m_plus, m_minus, m_mul, m_div, m_pow
	};
	return calc[op.toInt()](num1, num2);
}




void Solver::printAr(std::vector<IMathObject*>& ar) {
	for (int i = 0; i < ar.size(); i++) {
		size_t type = ar[i]->type();
		if (type == typeid(DoubleNumber).hash_code()) {
			auto* n1 = (DoubleNumber*)ar[i];
			std::cout << n1->number << std::endl;
		}

		//if (type == typeid(UnaryOperator).hash_code()) {
		//	auto* op = (UnaryOperator*)ar[i];
		//	std::cout << "\0()+-*/^"[op->toInt()] << std::endl;
		//}

		if (type == typeid(BinaryOperator).hash_code()) {
			auto* op = (BinaryOperator*)ar[i];
			std::cout << op->toInt() << ' ' << op->getPriority() << std::endl;
		}
		if (type == typeid(Bracket).hash_code()) {
			auto* br = (Bracket*)ar[i];
			std::cout << br->toInt() << ' ' << br->getPriority() << std::endl;
		}
	}
	std::cout << std::endl;
}

