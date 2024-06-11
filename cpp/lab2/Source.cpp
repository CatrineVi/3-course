#include <iostream>
#include <vector>

using namespace std;

double a1 = 4, b1 = 8, m = 3;
//double a1 = -6, b1 = 2, m = 3;
double h = (b1 - a1) / m;
//const double exp = 1e-4;

double f(double x)
{
	//return pow(x, 3) + 6 * pow(x, 2) - 0.02 * pow(2.71, x) - 14;
	return sqrt(x) - pow(cos(x), 2) - 2;
}
//double MP(double x)
//{
//	double x1 = x + h, x2 = x, x3 = x - h;
//	double y1 = f(x1), y2 = f(x2), y3 = f(x3);
//	double zm = INFINITY;
//	int it = 0;
//	do
//	{
//		it++;
//		double z1 = x1 - x3;
//		double z2 = x2 - x3;
//		double r = y3;
//		double d = z1 * z2 * (z1 - z2);
//		double p = ((y1 - y3) * z2 - (y2 - y3) * z1) / d;
//		double q = -((y1 - y3) * z2 * z2 - (y2 - y3) * z1 * z1) / d;
//		double D = sqrt(q * q - 4 * p * r);
//		double zm1 = (-q + D) / (2 * p);
//		double zm2 = (-q - D) / (2 * p);
//		zm = min(abs(zm1), abs(zm2));
//		x1 = x2;
//		x2 = x3;
//		y1 = y2;
//		y2 = y3;
//		x3 = x3 + zm;
//		y3 = f(x3);
//	} while (abs(zm) >= 1e-4 && it <= 100);
//	return x3;
//}
double MP(double x1)
{
	//double a=a1,b=b1, X = 0,x0=-1;
	double a = x1 - h, b = x1 + h, X = 0, x0 = a1;
	int it = 0;
	double e = abs(a - b);
	vector<double>x;
	if (f(a) * f(b) < 0)
	{
		while (e > 1e-4 && it<=100)
		{
			it++;
			double c = (a + b) / 2;
			double C = f(a);
			double B = (f(c) - f(a)) / (c - a) +
				((f(b) - f(c)) / (b - c) - (f(c) - f(a)) / (c - a)) / (b - a) * (a - c);
			double A = ((f(b) - f(c)) / (b - c) - (f(c) - f(a)) / (c - a)) / (b - a);
			double x1 = a - 2 * C / (B + sqrt(B * B - 4 * A * C));
			double x2 = a - 2 * C / (B - sqrt(B * B - 4 * A * C));
			if ((a <= x1 && x1 <= b) || (a >= x1 && x1 >= b))
				X = x1;
			if ((a <= x2 && x2 <= b) || (a >= x2 && x2 >= b))
				X = x2;
			if (f(a) * f(X) < 0)
			{
				a = a;
				b = X;
			}
			if (f(X) * f(b) < 0)
			{
				a = X;
				b = b;
			}
			e = abs(X - x0);
			cout << "e: " << e << endl;
			x0 = X;
			cout << "X: " << X << endl;
			x.push_back(X);

		}
	}
	return X;
}
int main()
{
	vector<double> X;
	//for (int i = 0; i < X.size(); i++)
		//cout << X[i] << "  ";
	vector<double> x;
	//for (double i = a1; i <= b1; i += h)
	x.push_back(a1);
	x.push_back(7);
	x.push_back(b1);
	//for (int i = 0; i < X.size(); i++)
	//	cout << X[i] << "  ";
	cout << endl;
	vector<double> z;
	for (int i = 0; i < x.size(); i++)
		z.push_back(MP(x[i]));
	for (int i = 0; i < z.size(); i++)
		cout << z[i] << "  ";
	return 0;
}