#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double a = 0, b = 1, y_0 = 1, N=10;
//sinx-1+2e^(-sinx)
double f(double x, double y)
{
	return sin(x) * cos(x) - y * cos(x);
}
double fx(double x, double y)
{
	return cos(x) * cos(x) - sin(x) * sin(x) + y * sin(x);
}
double fu(double x, double y)
{
	return -cos(x);
}
double ft(double x)
{
	return sin(x) - 1 + 2 * pow(2.7182818285, -sin(x));
}

void TSolv()
{
	double h = (b - a) / N;
	vector<double> x;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	vector<double> y;
	for (int i = 0; i < x.size(); i++)
		y.push_back(ft(x[i]));
	cout << "TSolv: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

double simpson(double x, double y)
{
	double h = (x - a) / N;
	double s = h / 6 * (f(a,y) + f(x,y));
	for (double i = a + h; i <= x - h; i += h)
		s += h / 6 * 2 * f(i,y);
	for (double i = a + h; i <= x; i += h)
		s += h / 6 * 4 * f((i + i - h) / 2,y);
	//cout << s << endl;
	return s;
}
double simpson(double x, double y, int n)
{
	double h = (x - a) / n;
	double s = h / 6 * (f(a, y) + f(x, y));
	for (double i = a + h; i <= x - h; i += h)
		s += h / 6 * 2 * f(i, y);
	for (double i = a + h; i <= x; i += h)
		s += h / 6 * 4 * f((i + i - h) / 2, y);
	//cout << s << endl;
	return s;
}

void Pikar()
{
	double h = (b - a) / N;
	vector<double> x;
	for (double i = a+h; i <= b; i += h)
		x.push_back(i);
	vector<double> y;
	y.push_back(y_0);
	for (int i = 0; i < x.size(); i++)
		y.push_back(y_0 + simpson(x[i],y[i]));
	cout << "pikar: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

void Eiler1()
{
	double h = (b - a) / N;
	vector<double> x;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	vector<double> y;
	y.push_back(y_0);
	for (int i = 0; i < x.size()-1; i++)
		y.push_back(y[i] + h * f(x[i], y[i]));
	cout << "eiler1: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

void Eiler2()
{
	double h = (b - a) / N;
	vector<double> x;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	vector<double> y;
	y.push_back(y_0);
	for (int i = 0; i < x.size()-1; i++)
		y.push_back(y[i] + h * f(x[i], y[i]) + h * h / 2. * (fx(x[i], y[i]) + fu(x[i], y[i]) * f(x[i], y[i])));
	cout << "eiler2: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

void Eiler3()
{
	double h = (b - a) / N;
	vector<double> x;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	vector<double> y;
	y.push_back(y_0);
	for (int i = 0; i < x.size()-1; i++)
	{
		double y2 = y[i] + h * f(x[i], y[i]);
		y.push_back(y[i] + h / 2 * (f(x[i], y2) + f(x[i + 1], y2)));
	}
	cout << "eiler3: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

void Runge_Kutta()
{
	double h = (b - a) / N;
	vector<double> x;
	vector<double> y;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	y.push_back(y_0);
	for (int i = 0; i < x.size()-1; i++)
	{
		double phi1 = h * f(x[i], y[i]);
		double phi2 = h * f(x[i] + h / 2., y[i] + phi1 / 2.);
		double phi3 = h * f(x[i] + h / 2., y[i] + phi2 / 2.);
		double phi4 = h * f(x[i] + h, y[i] + phi3);
		y.push_back(y[i] + 1 / 6. * (phi1 + 2 * phi2 + 2 * phi3 + phi4));
	}
	cout << "Runge_Kutta: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

vector<double> Runge_Kutta(int j)
{
	double h = (b - a) / N;
	vector<double> x;
	vector<double> y;
	for (double i = a; i <= a+j*h; i += h)
		x.push_back(i);
	y.push_back(y_0);
	for (int i = 0; i < x.size(); i++)
	{
		double phi1 = h * f(x[i], y[i]);
		double phi2 = h * f(x[i] + h / 2., y[i] + phi1 / 2.);
		double phi3 = h * f(x[i] + h / 2., y[i] + phi2 / 2.);
		double phi4 = h * f(x[i] + h, y[i] + phi3);
		y.push_back(y[i] + 1 / 6. * (phi1 + 2 * phi2 + 2 * phi3 + phi4));
	}
	return y;
}
double Runge_Kutta(double h)
{
	vector<double> x;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	double y = y_0;
	for (int i = 0; i < x.size(); i++)
	{
		double phi1 = h * f(x[i], y);
		double phi2 = h * f(x[i] + h / 2., y + phi1 / 2.);
		double phi3 = h * f(x[i] + h / 2., y + phi2 / 2.);
		double phi4 = h * f(x[i] + h, y + phi3);
		y = y + 1 / 6. * (phi1 + 2 * phi2 + 2 * phi3 + phi4);
	}
	return y;
}

void Adams()
{
	double h = (b - a) / N;
	vector<double> x;
	vector<double> y;
	for (double i = a; i <= b; i += h)
		x.push_back(i);
	y = Runge_Kutta(2);
	for (int i = 3; i < x.size()-1; i++)
		y.push_back(y[i] + h / 24 * (55 * f(x[i], y[i]) - 59 * f(x[i - 1], y[i - 1]) + 37 * f(x[i - 2], y[i - 2]) - 9 * f(x[i - 3], y[i - 3])));
	cout << "Adams: ";
	for (int i = 0; i < y.size(); i++)
		cout << y[i] << setw(10);
	cout << "\n\n";
}

void Runge_Romberg()
{
	double h = (b - a) / N;
	double Yh = Runge_Kutta(h);
	h = h / 2;
	double Yh2 = Runge_Kutta(h);
	double del = (Yh2 - Yh) / (pow(2, 4) - 1);
	while (abs(del) > 1e-5)
	{
		h = h / 2;
		Yh = Yh2;
		Yh2 = Runge_Kutta(h);
		del = (Yh2 - Yh) / (pow(2, 4) - 1);
	}
	cout << "\nRunge-Romberg: " << Yh2;
}

int main()
{
	TSolv();
	Pikar();
	Eiler1();
	Eiler2();
	Eiler3();
	Runge_Kutta();
	Adams();
	Runge_Romberg();
	return 0;
}