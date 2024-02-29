#include <iostream>

using namespace std;

double f(double x)
{
	return 2 * x - 4 * cos(x) - 0.6;
}
double f1(double x)
{
	return (4 * cos(x) + 0.6) / 2;
}
double diff1(double x)
{
	return -4 * sin(x) / 2;
}
double f2(double x)
{
	return acos((2 * x + 0.6) / 4);
}
double diff2(double x)
{
	return (-1 / 2) * (1 / sqrt(1 - 1 / 4 * pow(x + 0.3, 2)));
}
double fi(double x)
{
	return x - 0.01 * 2 * x + 0.01 * 4 * cos(x) + 0.01 * 0.6;
}
double diffi(double x)
{
	return 1 - 0.01 * 2 - 0.01 * 4 * sin(x);
}
//double dif1(double x)
//{
//	double h = 0.001;
//	return (f(x + h) - f(x - h) / (2 * h));
//}
double dif1(double x)
{
	return 2 + 4 * sin(x);
}
//double dif2(double x)
//{
//	double h = 0.1;
//	return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
//}
double dif2(double x)
{
	return 4 * cos(x);
}


double a = -0.5, b = 1.5, pMin;
double e = 0.00001;

void HalfDiv()
{
	double c = (a + b) / 2;
	double a0 = a, b0 = b;
	while (abs(b0 - a0) > e) {
		c = (a0 + b0) / 2;
		if (f(a0) * f(c) < 0) b0 = c;
		else a0 = c;
	}
	cout << "HalfDiv: x = " << c << " f(c) = " << f(c) << endl;;
}

void NR()
{
	double x = a;
	do {
		x = x - f(x) / dif1(x);
	} while (abs(f(x)) > e);
	cout << "NR: x = " << x << endl;
}

void Sek()
{
	double x = a;
	do {
		x = x - f(x) / (f(b) - f(x)) * (b - x);
	} while (abs(f(x)) > e);
	cout << "Sek: x = " << x << endl;
}

void Comb()
{
	double x0 = a, x1 = b, x01, x11;
	while (abs(x1 - x0) > e)
	{
		x0 = x0 - f(x0) / (f(x1) - f(x0)) * (x1 - x0);
		x1 = x1 - f(x1) / dif1(x1);
	}
	cout << "Comb: x = " << x0 << endl;
}

void ProstIter()
{
	double x0 = a;
	//double x1 = f1(x0), q = abs(diff1(a));
	//double x1 = f2(x0), q = abs(diff2(a));
	double x1 = fi(x0), q = abs(diffi(a));
	while (q * abs(x1 - x0) / (1 - q) > e)
	{
		x0 = x1;
		//x1 = f1(x0);
		//x1 = f2(x0);
		x1 = fi(x0);
	}
	cout << "ProstIter: x = " << x0 << endl;
}

int main()
{
	HalfDiv();
	NR();
	Sek();
	Comb();
	ProstIter();
	return 0;
}