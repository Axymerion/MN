#pragma once

#include <vector>
#include <iostream>
#include <cmath>

class Matrix
{
private:
	double** data;
	int h;
	int w;

public:
	Matrix(std::vector<double> data, int height, int width): h(height), w(width)
	{
		this->data = new double*[this->h];
		for (int i = 0; i < this->h; i++)
		{
			this->data[i] = new double[this->w];
		}

		int k = 0;
		for (int i = 0; i < this->h; i++)
		{
			for (int j = 0; j < this->w; j++)
			{
				this->data[i][j] = data[k];
				k++;
			}
		}
	}

	Matrix(int height, int width) : h(height), w(width)
	{
		this->data = new double* [this->h];
		for (int i = 0; i < this->h; i++)
		{
			this->data[i] = new double[this->w];
		}
	}

	Matrix(const Matrix& m) : h(m.h), w(m.w)
	{
		this->data = new double* [this->h];
		for (int i = 0; i < this->h; i++)
		{
			this->data[i] = new double[this->w];
		}

		for (int i = 0; i < this->h; i++)
		{
			for (int j = 0; j < this->w; j++)
			{
				this->data[i][j] = m.data[i][j];
			}
		}
	}

	~Matrix()
	{
		for (int i = 0; i < this->h; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}

	int getHeight()
	{
		return this->h;
	}

	int getWidth()
	{
		return this->w;
	}

	double getCell(int a, int b)
	{
		return this->data[a][b];
	}

	void setCell(int a, int b, double c)
	{
		if (a >= this->h || b >= this->w)
			return;

		this->data[a][b] = c;
	}

	void Print()
	{
		for (int i = 0; i < this->h; i++)
		{
			for (int j = 0; j < this->w; j++)
			{
				std::cout << this->data[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}

	Matrix T()
	{
		Matrix temp(this->w, this->h);
		for (int i = 0; i < this->h; i++)
		{
			for (int j = 0; j < this->w; j++)
			{
				temp.data[j][i] = this->data[i][j];
			}
		}
		return temp;
	}

	Matrix Sub(int r, int c)
	{
		Matrix temp(this->h - 1, this->w - 1);

		int k = 0;
		for (int i = 0; i < temp.h; i++)
		{
			if (i == r)
			{
				k++;
			}

			int l = 0;
			for (int j = 0; j < temp.w; j++)
			{
				if (l == c)
				{
					l++;
				}
				temp.data[i][j] = this->data[k][l];
				l++;
			}
			k++;
		}

		return temp;
	}

	double Det()
	{
		if (this->h == 1)
			return this->data[0][0];

		double det = 0;
		for (int i = 0; i < this->h; i++)
		{
			det += pow(-1, i + 2) * this->data[0][i] * Sub(0, i).Det();
		}

		return det;
	}

	Matrix Comp()
	{
		Matrix temp(this->h, this->w);

		for (int i = 0; i < temp.h; i++)
		{
			for (int j = 0; j < temp.w; j++)
			{
				temp.data[i][j] = pow(-1, i + j + 2) * Sub(i, j).Det();
			}
		}

		return temp;
	}

	Matrix Inv()
	{
		return Comp().T() * (1 / Det());
	}
	
	Matrix operator*(Matrix b)
	{
		Matrix temp(this->h, b.w);

		for (int i = 0; i < temp.h; i++)
		{
			for (int j = 0; j < temp.w; j++)
			{
				double sum = 0;
				for (int k = 0; k < this->w; k++)
				{
					sum += this->data[i][k] * b.data[k][j];
				}
				temp.data[i][j] = sum;
			}
		}
		return temp;
	}

	Matrix operator*(double a)
	{
		Matrix temp(this->h, this->w);

		for (int i = 0; i < this->h; i++)
		{
			for (int j = 0; j < this->w; j++)
			{
				temp.data[i][j] = this->data[i][j] * a;
			}
		}
		return temp;
	}
};

class LinMatrix : public Matrix
{
public:
	using Matrix::Matrix;
	Matrix Subs(int r, std::vector<double> v)
	{
		Matrix temp = *this;

		for (int i = 0; i < temp.getHeight(); i++)
		{
			temp.setCell(i, r, v[i]);
		}
		return temp;
	}

	Matrix Solve(std::vector<double> v)
	{
		Matrix out(this->getWidth(), 1);
		double w = Det();
		for (int i = 0; i < v.size(); i++)
		{
			out.setCell(i, 0, (Subs(i, v).Det() / w));
		}
		return out;
	}
};