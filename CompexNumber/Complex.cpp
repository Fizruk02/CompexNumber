#include "Complex.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

namespace Im {
	Complex::Complex() {
		this->cnum = { 0, 0, (double)Period::ONE };
	}
	Complex::Complex(double Re, double Im) {
		this->cnum = { Re, Im, (double)Period::ONE };
	}
	Complex::~Complex() {}

	Complex Complex::getNumber() {
		return *this;
	}
	Complex Complex::Ñonjugate() {
		Complex temp;
		temp.cnum = this->cnum;
		temp.cnum[1] = -temp.cnum[1];
		return temp;
	}

	Complex Complex::operator+(const Complex& cn) {
		Complex temp(this->cnum[0] + cn.cnum[0], this->cnum[1] + cn.cnum[1]);
		return temp;
	}
	Complex Complex::operator+=(const Complex& cn) {
		this->cnum[0] += cn.cnum[0];
		this->cnum[1] += cn.cnum[1];
		return *this;
	}
	Complex Complex::operator-(const Complex& cn) {
		Complex temp(this->cnum[0] - cn.cnum[0], this->cnum[1] - cn.cnum[1]);
		return temp;
	}
	Complex Complex::operator-=(const Complex& cn) {
		this->cnum[0] -= cn.cnum[0];
		this->cnum[1] -= cn.cnum[1];
		return *this;
	}
	Complex Complex::operator*(const Complex& cn) {
		Complex temp(this->cnum[0] * cn.cnum[0] - this->cnum[1] * cn.cnum[1], this->cnum[0] * cn.cnum[1] + this->cnum[1] * cn.cnum[0]);
		return temp;
	}
	Complex Complex::operator*=(const Complex& cn) {
		this->cnum[0] = this->cnum[0] * cn.cnum[0] - this->cnum[1] * cn.cnum[1];
		this->cnum[1] = this->cnum[0] * cn.cnum[1] + this->cnum[1] * cn.cnum[0];
		return *this;
	}
	Complex Complex::operator/(const Complex& cn) {
		Complex temp((this->cnum[0] * cn.cnum[0] + this->cnum[1] * cn.cnum[1]) / (std::pow(cn.cnum[0], 2) + std::pow(cn.cnum[1], 2)), (this->cnum[1] * cn.cnum[0] - this->cnum[0] * cn.cnum[1]) / (std::pow(cn.cnum[0], 2) + std::pow(cn.cnum[1], 2)));
		return temp;
	}
	Complex Complex::operator/=(const Complex& cn) {
		double x = this->cnum[0];
		double yi = this->cnum[1];
		this->cnum[0] = (x * cn.cnum[0] + yi * cn.cnum[1]) / (std::pow(cn.cnum[0], 2) + std::pow(cn.cnum[1], 2));
		this->cnum[1] = (yi * cn.cnum[0] - x * cn.cnum[1]) / (std::pow(cn.cnum[0], 2) + std::pow(cn.cnum[1], 2));
		return *this;
	}

	Complex Complex::pow(const Complex& cn, unsigned int n) {
		Complex temp = cn;
		//double x = cn.cnum[0], yi = cn.cnum[1];
		//if (x && yi) {
		//	double r = std::pow(sqrt(std::pow(x, 2) + std::pow(yi, 2)), n);
		//	double fi = atan(yi / x) * n;
		//	double cosx = r * cos(fi);
		//	double sinx = r * sin(fi);
		//	if (std::abs(cosx) < std::pow(0.1, 15))
		//		cosx = 0;
		//	if (std::abs(sinx) < std::pow(0.1, 15))
		//		sinx = 0;
		//	temp.cnum = { cosx, sinx, 1 };
		//}
		//else if (!x && yi) temp.cnum = { x, std::pow(yi, n % 4), (double)(n % 4) };
		//else if (x && !yi) temp.cnum = { std::pow(x, n), yi, (double)Period::ONE };
		//else temp.cnum = { x, yi, (double)Period::ONE };
		for (int i = 0; i < n; i++) {
			std::cout << temp << std::endl;
			temp *= cn;
		}
			
		return temp;
	}
	std::vector<Complex> Complex::sqrn(const Complex& cn, int n){
		std::vector<Complex> sqrn;
		
		const double PI = 3.141592653589793;
		double x = cn.cnum[0], yi = cn.cnum[1];
		double r = std::pow(sqrt(std::pow(x, 2) + std::pow(yi, 2)), n);

		for (int i = 0; i < n; i++) {
			Complex temp;
			double fi = (atan(yi / x) + 2 * PI * i) / n;
			double cosx = r * cos(fi);
			double sinx = r * sin(fi);
			if (std::abs(cosx) < std::pow(0.1, 15)) cosx = 0;
			if (std::abs(sinx) < std::pow(0.1, 15)) sinx = 0;
			temp.cnum = { cosx, sinx, 1 };
			sqrn.push_back(temp);
		}

		return sqrn;
	}

	std::ostream& operator<<(std::ostream& os, const Complex& cn) {
		std::vector<double> cnum = cn.cnum;
		double x = cnum[0];
		double yi = cnum[1];
		Period period = (Period)cnum[2];

		std::string num = "";
		short k = (yi < 0) ? k = 1 : 2;

		if (yi && x) {
			std::string pm = (std::pow(-1, k) > 0) ? " + " : " - ";
			switch (period) {
			case Period::ZERO: num += (std::to_string(x + std::pow(-1, k) * std::abs(yi))); break;
			case Period::ONE: num += (std::to_string(x) + pm + std::to_string(std::abs(yi)) + "i"); break;
			case Period::TWO: num += (std::to_string(x - std::pow(-1, k) * std::abs(yi))); break;
			case Period::TREE: num += (std::to_string(x) + pm + std::to_string(std::abs(yi)) + "i"); break;
			}
		}
		else if (yi && !x) {
			std::string pm = (std::pow(-1, k) > 0) ? "" : "-";
			switch (period) {
			case Period::ZERO: num += (std::to_string(std::pow(-1, k) * std::abs(yi))); break;
			case Period::ONE: num += (pm + std::to_string(std::abs(yi)) + "i"); break;
			case Period::TWO: num += (std::to_string(x - std::pow(-1, k) * std::abs(yi))); break;
			case Period::TREE: num += (pm + std::to_string(std::abs(yi)) + "i"); break;
			}
		}
		else num += std::to_string(x);
		os << num;
		return os;
	}
	std::istream& operator>>(std::istream& is, Complex& cn) {
		is >> cn.cnum[0] >> cn.cnum[1];
		cn.cnum[2] = (double)Period::ONE;
		return is;
	}
}