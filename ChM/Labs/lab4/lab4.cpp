#include <iostream>
#include <vector>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#define pi 3.14159265
using namespace std;
int N = 4, k = 0;
double h = 0.1;
double f(double x)
{
	return N / 2 * exp(-x / (k + 4)) * cos(x / (k + N)) + pi * N / 2;
}
double f11(double x1, double x)
{
	return (f(x1) - f(x)) / h;
}
double f12(double xp1, double xm1)
{
	return (f(xp1) - f(xm1)) / (2*h);
}
double f2(double xp1, double x, double xm1)
{
	return (f(xm1) - 2 * f(x) + f(xp1)) / pow(h, 2);
}
int main()
{
	vector<double> x;
	for (double i = 1; i <= 2.1; i += 0.1)
		x.push_back(i);
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << "  ";
	cout << endl;
	vector<double> v1;
	for (int i = 0; i < x.size()-1; i++)
		v1.push_back(f11(x[i + 1], x[i]));

	for (int i = 0; i < v1.size(); i++)
		cout << setw(5) << v1[i];

	cout << endl;
	vector<double> v2;
	for (int i = 1; i < x.size()-1; i++)
		v2.push_back(f12(x[i + 1], x[i-1]));
	for (int i = 0; i < v2.size(); i++)
		cout << setw(5) << v2[i];

	cout << endl;
	vector<double> v3;
	for (int i = 1; i < x.size() - 1; i++)
		v3.push_back(f2(x[i + 1], x[i], x[i - 1]));
	for (int i = 0; i < v3.size(); i++)
		cout << "   " << v3[i];
	return 0;
}