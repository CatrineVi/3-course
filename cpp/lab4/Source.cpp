#include <iostream>
#include <vector>

using namespace std;

//lagrang
double a = 5, b = 8;
int m = 4;

double f(double x)
{
	return sqrt(x) - pow(cos(x), 2);
}

double Mn_Lagr(vector<double> x, double xt, int kol)
{
	double e, p = 0;
	for (int k = 0; k < kol; k++)
	{
		e = 1;
		for (int i = 0; i < kol; i++)
			if (i != k) e *= ((xt - x[i]) / (x[k] - x[i]));
		p += e * f(x[k]);
	}
	return p;
}

void Rezult()
{
	double x, h, h1;
	int i, n;
	vector<double> mas_x(m + 1);
	vector<double> mas_y_t(n + 1);
	h = (b - a) / (m - 1);
	h1 = (b - a) / (n - 1);
	for (x = a, i = 0; i < m; i++)
	{
		mas_x[i] = x;
		x += h;
	}
	for (x = a, i = 0; i < n; i++, x += h1)
	{
		mas_y_t[i] = Mn_Lagr(mas_x, x, m);
	}
}

int main()
{

	return 0;
}