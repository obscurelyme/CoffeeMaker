#include "Complex.hpp"

Complex::Complex(double r, double i): real(r), imaginary(i) {}

bool operator==(const Complex& lhs, const Complex& rhs) {
  return lhs.real == rhs.real && rhs.imaginary == lhs.imaginary;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
	return Complex(lhs.real + rhs.real, lhs.imaginary + rhs.imaginary);
}
