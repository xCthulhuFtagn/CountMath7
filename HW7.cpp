#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

double Simpson(double (*func)(double), double bot, double top, unsigned n) {
	double S_n, h = (top - bot) / n;
	S_n = func(bot) + func(top);
	for (unsigned i = 1; i < n - 1; i += 2) {
		S_n += 4 * (func(bot + i * h));
		S_n += 2 * (func(bot + (i + 1) * h));
	}
	S_n += 4 * (func(bot + (n - 1) * h));
	S_n *= h / 3;
	return S_n;
}

double Rectangle(double (*func)(double), double bot, double top, unsigned n) {
	double S_n = 0, h = (top - bot) / n;
	unsigned i;
	for (i = 0; i < n; ++i) {
		S_n += func(bot + h * i + h / 2);
	}
	S_n *= h;
	return S_n;
}

double Trapezoid(double (*func)(double), double bot, double top, unsigned n) {
	double S_n = (func(top) + func(bot)) / 2, h = (top - bot) / n;
	for (unsigned i = 1; i < n; ++i) {
		S_n += func(bot + h * i);
	}
	S_n *= h;
	return S_n;
}

double Integration(double (*func)(double), double(*method)(double (double), double, double, unsigned), double bot, double top, double step) {
	return method(func, bot, top, (top - bot)/step);
}

double func(double x){  return 1/(pow(x, 4) + 16);  }

double Accuracy(double a, double b, double a_step, double b_step, size_t p){
    return fabs((a-b)/(pow((b_step/a_step), p) - 1));
}

int main()
{
    double a = Integration(func, Simpson, 0, 2, 0.5), b = Integration(func, Rectangle, 0, 2, 0.5), c = Integration(func, Trapezoid, 0, 2, 0.5), 
        d = Integration(func, Trapezoid, 0, 2, 0.5), e = Integration(func, Rectangle, 0, 2, 0.25), f = Integration(func, Trapezoid, 0, 2, 0.25);
	cout << "Given function integrated by Simpson's method with step = 0.5: " << a << endl;
	cout << "Given function integrated by Rectangle method with step = 0.5: " << b << endl;
	cout << "Given function integrated by Trapezoid method with step = 0.5: " << c <<endl;	
    cout << "Given function integrated by Simpson's method with step = 0.25: " << d << endl;
	cout << "Given function integrated by Rectangle method with step = 0.25: " << e << endl;
	cout << "Given function integrated by Trapezoid method with step = 0.25: " << f <<endl;
    cout << "Accuracy of Simpson: " << Accuracy(a, d, 0.5, 0.25, 4) << endl;
    cout << "Accuracy of Rectangle method: " << Accuracy(b, e, 0.5, 0.25, 2) << endl;
    cout << "Accuracy of Trapezoid method: " << Accuracy(c, f, 0.5, 0.25, 2) << endl;

	return 0;
}