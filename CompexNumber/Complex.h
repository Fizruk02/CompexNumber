#pragma once
#include <vector>
#include <iostream>

namespace Im {
	enum Period { ZERO, ONE, TWO, TREE };

	class Complex
	{
	private:
		std::vector<double> cnum;
		Complex getNumber();
	public:
		Complex();
		Complex(double Re, double Im);
		~Complex();	
		Complex Ñonjugate();

		Complex operator+(const Complex& cn);
		Complex operator+=(const Complex& cn);
		Complex operator-(const Complex& cn);
		Complex operator-=(const Complex& cn);
		Complex operator*(const Complex& cn);
		Complex operator*=(const Complex& cn);
		Complex operator/(const Complex& cn);
		Complex operator/=(const Complex& cn);

		static Complex pow(const Complex& cn, unsigned int n);
		static std::vector<Complex> sqrn(const Complex& cn, int n);

		friend std::istream& operator>>(std::istream& is, Complex& cn);
		friend std::ostream& operator<<(std::ostream& os, const Complex& cn);
	};
}

