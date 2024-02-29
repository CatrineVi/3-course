#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#define pi 3.14159265
double eps = 0.001;

using namespace std;

double a = 1, b = -2, c = 1, d = -0.7, e = 1, f = pi / 2, g = 2, h = -0.6;

double F(double x, double y)
{
	return sin(a * x + b) + c * y + d;
}
double difFx(double x, double y)
{
	return cos(a * x + b) * a;
}
double difFy(double x, double y)
{
	return c;
}
double G(double x, double y)
{
	return cos(e * y + f) + g * x + h;
}
double difGx(double x, double y)
{
	return g;
}
double difGy(double x, double y)
{
	return -e * sin(e * y + f);
}
double psi(double x, double y)
{
	return pow(F(x, y), 2) + pow(G(x, y), 2);
}
double difPSIx(double x, double y)
{
	return 2 * sin(a * x + b) * cos(a * x + b) * a + 2 * c * y * a * cos(a * x + b) + 2 * d * a * cos(a * x + b) + 2 * g * cos(e * y + f) + 2 * g * g * x + 2 * h * g;
}
double difiPSIy(double x, double y)
{
	return 2 * c * sin(a * x + b) + 2 * c * c * y + 2 * d * c - 2 * e * cos(e * y + f) * sin(e * y + f) - 2 * g * e * x * sin(e * y + f) - 2 * h * e * sin(e * y + f);
}

double productForX(double x, double y)
{
	double det = difFx(x, y) * difGy(x, y) - difGx(x, y) * difFy(x, y);
	return cos(y) / (cos(x - 2) * cos(y) + 2) * F(x, y) + 1 / (cos(x - 2) * cos(y) + 2)*G(x,y);
	//det * difGy(x, y) * F(x, y) + det * (-difFy(x, y)) * G(x, y);
}
double productForY(double x, double y)
{
	double det = difFx(x, y) * difGy(x, y) - difGx(x, y) * difFy(x, y);
	return 2 / (cos(x - 2) * cos(y) + 2) * F(x, y) - cos(x - 2) / (cos(x - 2) * cos(y) + 2) * G(x, y);
	///det * (-difGx(x, y)) * F(x, y) + det * difFx(x, y) * G(x, y);
}
double Norm(double x, double x0, double y, double y0)
{
	double norm = 0;
	norm = pow((x - x0), 2) + pow((y - y0), 2);
	norm = sqrt(norm);
	return norm;
}
void newton()
{
	double x = 0, x0, y = 0, y0;
	do
	{
		x0 = x; y0 = y;
		x = x0 - productForX(x0,y0);
		y = y0 - productForY(x0,y0);
		cout << "Newton: " << x << " " << y << endl;
	} while (Norm(x,x0,y,y0) > eps);
	cout << "Newton: " << x << " " << y << endl;
	cout << "F = " << F(x, y) << "   G = " << G(x, y) << endl;
}

void spusk()
{
	double x = 0, x0, y = 0, y0, alfa = 1.0/2;
	while (psi(x, y) > 2 * eps * eps)
	{
		x0 = x; y0 = y;
		x = x0 - alfa * difPSIx(x0, y0);
		y = y0 - alfa * difiPSIy(x0, y0);
		if (psi(x, y) > psi(x0, y0))
			alfa /= 2.0;
	}
	cout << "Spusk: " << x << " " << y << endl;
	cout << "F = " << F(x, y) << "   G = " << G(x, y) << endl;
}

int main()
{
	newton();
	spusk();

	return 0;
}