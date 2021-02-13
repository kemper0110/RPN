#pragma once
#include <cstdint>
namespace dl {
	enum class math_funcs {
		Sin, Cos, Tg, Ctg, Arcsin, Arccos, Arctg, Arcctg
	};

	double sin(double x) {
		while (x >= 6.28)
			x -= 6.28;
		while (x <= -6.28)
			x += 6.28;

		double sum = x;
		uint64_t fac = 2;
		double _x = x * x;

		int factor[2]{ 1, -1 };
		for (int i = 3; i < 20; i += 2) {
			fac *= i;
			_x *= x;
			sum += factor[i / 2 & 1] * _x / fac;
			fac *= i + 1;
			_x *= x;
		}
		return sum;
	}
}