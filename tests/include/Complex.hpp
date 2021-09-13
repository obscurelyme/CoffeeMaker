#ifndef _coffeemaker_complex_hpp
#define _coffeemaker_complex_hpp

class Complex {
  private:
    double real;
    double imaginary;
    /**
     * operators defined within a class take 1 argument, and
     * operators defined outside a class take 2 arguments
     */
    friend bool operator==(const Complex& lhs, const Complex& rhs);
		friend Complex operator+(const Complex& lhs, const Complex& rhs);

  public:
    Complex(double r, double i = 0);
};

#endif
