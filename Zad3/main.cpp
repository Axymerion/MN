#include <iostream>
#include "matrices.h"

int main()
{
	//Elementy do macierzy wpisujemy jako wektor, podaj¹c je jako kolejne wiersze
	Matrix y({ -1.99, -2.24, -3.3, -5.01, -7.78, -11.3, -15.67, -20.48 }, 8, 1);
	Matrix x({ 1, 0, 0, 1, 1, 1, 1, 2, 4, 1, 3, 9, 1, 4, 16, 1, 5, 25, 1, 6, 36, 1, 7, 49 }, 8, 3);
	((x.T()*x).Inv()*(x.T()*y)).Print();
}