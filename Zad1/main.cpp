#include <iostream>
#include <functional>
#include "matrices.h"

double Int(std::function<double(double)> f, double a, double b, double h = 0.0001)
{
	double out = 0;
	for (double i = a; i < b; i += h)
	{
		out += f(i) * h;
	}
	return out;
}

Matrix Approx(std::function<double(double)> f, int st, double a, double b)
{
	LinMatrix A(st, st);
	int i = st - 1;
	int j = st - 1;
	int k = 0;

	while (i >= 0 && j >= 0)
	{
		for (int l = 0; l <= k; l++)
		{
			A.setCell(l, k - l, Int([i, j](double x) { return pow(x, i) * pow(x, j); }, a, b));
		}

		if (i == j)
		{
			i--;
		}
		else
		{
			j--;
		}
		k++;
	}
	
	std::vector<double> B;
	for (int i = 0; i < st; i++)
	{
		B.push_back(Int([i, f, st](double x) {return f(x)*pow(x, st-i-1) ; }, a, b));
	}

	return A.Solve(B);
}

int main()
{
	auto f = [](double x) {return cbrt(x); };
	Matrix A = Approx(f, 3, 0, 2);
	A.Print();
}
