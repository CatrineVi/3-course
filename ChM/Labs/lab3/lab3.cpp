#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#define pi 3.14159265
double eps = 0.001;

using namespace std;

vector<double> x = { -2,0,1,2,3 };
vector<double> y = { 67,9,4,-1,17 };

vector<double> x1 = { pi / 6,pi / 4,pi / 3,pi / 2 };
double f(double x)
{
	return cos(x) / sin(x);
}

vector<double> xe = { -2,-1,0,1 };
vector<double> ye = { 8,0,-4,2 };
vector<double> ye1 = { 244,-13,0,31 };
vector<double> ye2 = { INT32_MIN,46,6,INT32_MIN };

vector<vector<double>>Hx = {
	{1,xe[0],pow(xe[0],2),pow(xe[0],3),pow(xe[0],4),
	pow(xe[0],5),pow(xe[0],6),pow(xe[0],7),
	pow(xe[0],8),pow(xe[0],9)},
	{1,xe[1],pow(xe[1],2),pow(xe[1],3),pow(xe[1],4),
	pow(xe[1],5),pow(xe[1],6),pow(xe[1],7),
	pow(xe[1],8),pow(xe[1],9)},
	{1,xe[2],pow(xe[2],2),pow(xe[2],3),pow(xe[2],4),
	pow(xe[2],5),pow(xe[2],6),pow(xe[2],7),
	pow(xe[2],8),pow(xe[2],9)},
	{1,xe[3],pow(xe[3],2),pow(xe[3],3),pow(xe[3],4),
	pow(xe[3],5),pow(xe[3],6),pow(xe[3],7),
	pow(xe[3],8),pow(xe[3],9)},
	{0,1,2 * x[0],3 * pow(xe[0],2),4 * pow(xe[0],3),5 * pow(xe[0],4),
	6 * pow(xe[0],5),7 * pow(xe[0],6),8 * pow(xe[0],7),9 * pow(xe[0],8)},
	{0,1,2 * x[1],3 * pow(xe[1],2),4 * pow(xe[1],3),5 * pow(xe[1],4),
	6 * pow(xe[1],5),7 * pow(xe[1],6),8 * pow(xe[1],7),9 * pow(xe[1],8)},
	{0,1,2 * x[2],3 * pow(xe[2],2),4 * pow(xe[2],3),5 * pow(xe[2],4),
	6 * pow(xe[2],5),7 * pow(xe[2],6),8 * pow(xe[2],7),9 * pow(xe[2],8)},
	{0,1,2 * x[3],3 * pow(xe[3],2),4 * pow(xe[3],3),5 * pow(xe[3],4),
	6 * pow(xe[3],5),7 * pow(xe[3],6),8 * pow(xe[3],7),9 * pow(xe[3],8)},
	{0,0,2,6 * xe[1],12 * pow(xe[1],2),20 * pow(xe[1],3),30 * pow(xe[1],4),
	42 * pow(xe[1],5),56 * pow(xe[1],6),72 * pow(xe[1],7)},
	{0,0,2,6 * xe[2],12 * pow(xe[2],2),20 * pow(xe[2],3),30 * pow(xe[2],4),
	42 * pow(xe[2],5),56 * pow(xe[2],6),72 * pow(xe[2],7)}
};

vector<double> Hy = { ye[0],ye[1],ye[2],ye[3],ye1[0],ye1[1],ye1[2],ye1[3],ye2[1],ye2[2] };

void print10(vector < double> l)
{
	if (l[9] > 0)
		cout << l[9] << "x^9";
	else if (l[9] < 0)
		cout << " - " << abs(l[9]) << "x^9";
	for (int i = 8; i >= 2; i--)
	{
		if (l[i] > 0)
			cout << " + " << l[i] << "x^" << i;
		else if (l[i] < 0)
			cout << " - " << abs(l[i]) << "x^" << i;
	}
	if (l[1] > 0)
		cout << " + " << l[1] << "x";
	else if (l[1] < 0)
		cout << " - " << abs(l[1]) << "x";
	if (l[0] > 0)
		cout << " + " << l[0];
	else if (l[0] < 0)
		cout << " - " << abs(l[0]);
}
void print5(vector < double> l)
{
	if (l[0] > 0)
		cout << l[0] << "x^4";
	else if (l[0] < 0)
		cout << " - " << abs(l[0]) << "x^4";
	if (l[1] > 0)
		cout << " + " << l[1] << "x^3";
	else if (l[1] < 0)
		cout << " - " << abs(l[1]) << "x^3";
	if (l[2] > 0)
		cout << " + " << l[2] << "x^2";
	else if (l[2] < 0)
		cout << " - " << abs(l[2]) << "x^2";
	if (l[3] > 0)
		cout << " + " << l[3] << "x";
	else if (l[3] < 0)
		cout << " - " << abs(l[3]) << "x";
	if (l[4] > 0)
		cout << " + " << l[4];
	else if (l[4] < 0)
		cout << " - " << abs(l[4]);
}
void print4(vector < double> l)
{
	if (l[0] > 0)
		cout << l[0] << "x^3";
	else if (l[0] < 0)
		cout << " - " << abs(l[0]) << "x^3";
	if (l[1] > 0)
		cout << " + " << l[1] << "x^2";
	else if (l[1] < 0)
		cout << " - " << abs(l[1]) << "x^2";
	if (l[2] > 0)
		cout << " + " << l[2] << "x";
	else if (l[2] < 0)
		cout << " - " << abs(l[2]) << "x";
	if (l[3] > 0)
		cout << " + " << l[3];
	else if (l[3] < 0)
		cout << " - " << abs(l[3]);
}
vector<double> Pch(int i)
{
	vector<double>v = x;
	v.erase(v.begin() + i);
	vector<double> p = { 1, -v[0] - v[1] - v[2] - v[3],
		(-v[0] - v[1]) * (-v[2] - v[3]) + (-v[0]) * (-v[1]) + (-v[2]) * (-v[3]),
		(-v[0] - v[1]) * (-v[2]) * (-v[3]) + (-v[2] - v[3]) * (-v[0]) * (-v[1]),
		(-v[0]) * (-v[1]) * (-v[2]) * (-v[3]) };
	return p;
}
vector<double> PchF(int i)
{
	vector<double>v = x1;
	v.erase(v.begin() + i);
	vector<double> p = { 1, -v[0] - v[1] - v[2],
		(-v[0]) * (-v[1]) + (-v[1]) * (-v[2]) + (-v[0]) * (-v[2]), 
		(-v[0])* (-v[1]) * (-v[2]) };
	return p;
}
double Pz(int i)
{
	double p = 1;
	for (int j = 0; j < x.size(); j++)
	{
		if (j != i)
			p *= (x[i] - x[j]);
	}
	return p;
}
double PzF(int i)
{
	double p = 1;
	for (int j = 0; j < x1.size(); j++)
	{
		if (j != i)
			p *= (x1[i] - x1[j]);
	}
	return p;
}
void lagr()
{
	vector<double>l;
	vector<double>v;
	for (int i = 0; i < y.size(); i++)
		v.push_back(y[i] / Pz(i));
	for (int i = 0; i < y.size(); i++)
	{
		double s = 0;
		for (int j = 0; j < y.size(); j++)
			s += v[j] * Pch(j)[i];
		l.push_back(s);
	}
	print5(l);
}
void lagrF()
{
	vector<double>l;
	vector<double>v;
	for (int i = 0; i < x1.size(); i++)
		v.push_back(f(x1[i]) / PzF(i));
	for (int i = 0; i < x1.size(); i++)
	{
		double s = 0;
		for (int j = 0; j < x1.size(); j++)
			s += v[j] * PchF(j)[i];
		l.push_back(s);
	}
	print4(l);
}

double newtonK(int n)
{
	double s = 0;
	for (int k = 0; k <= n; k++)
	{
		double p = 1;
		for (int i = 0; i <= n; i++)
		{
			if (i != k)
				p *= (x[k] - x[i]);
		}
		s += y[k] / p;
	}
	return s;
}
double newtonKf(int n)
{
	double s = 0;
	for (int k = 0; k <= n; k++)
	{
		double p = 1;
		for (int i = 0; i <= n; i++)
		{
			if (i != k)
				p *= (x1[k] - x1[i]);
		}
		s += f(x1[k]) / p;
	}
	return s;
}

vector<double> newtonM(int n,int k)
{
	int m; vector<double> z;
	if (k == 1) {
		m = x.size(); z = x;
	}
	if (k == 2) {
		m = x1.size(); z = x1;
	}
	vector<double> v(m);

	if (n == 0)
	{
		v[m-1] = 1;
	}
	else if (n == 1)
	{
		v[m-2] = 1;
		v[m-1] = -z[0];
	}
	else if (n == 2)
	{
		v[m-3] = 1;
		v[m-2] = -z[0] - z[1];
		v[m-1] = (-z[0]) * (-z[1]);
	}
	else if (n == 3)
	{
		v[m-4] = 1;
		v[m-3] = -z[0] - z[1] - z[2];
		v[m-2] = (-z[0]) * (-z[1]) + (-z[0]) * (-z[2]) + (-z[1]) * (-z[2]);
		v[m-1] = (-z[0]) * (-z[1]) * (-z[2]);
	}
	else if (n == 4)
	{
		v[m-5] = 1;
		v[m-4] = -z[0] - z[1] - z[2] - z[3];
		v[m-3] = (-z[0]) * (-z[1]) + (-z[0]) * (-z[2]) + (-z[0]) * (-z[3]) + 
			(-z[1]) * (-z[2]) + (-z[1]) * (-z[3]) + (-z[2]) * (-z[3]);
		v[m-2] = (-z[0]) * (-z[1]) * (-z[2]) + (-z[0]) * (-z[1]) * (-z[3]) +
			(-z[0]) * (-z[2]) * (-z[3]) + (-z[1]) * (-z[2]) * (-z[3]);
		v[m-1] = (-z[0]) * (-z[1]) * (-z[2]) * (-z[3]);
	}

	return v;
}

void newton()
{
	vector<double> n;
	vector<vector<double>> v;
	for (int i = 0; i < x.size(); i++)
		v.push_back(newtonM(i, 1));
	for (int i = 0; i < x.size(); i++)
	{
		double s = 0;
		for (int j = 0; j < x.size(); j++)
		{
			s += newtonK(j) * v[j][i];
		}
		n.push_back(s);
	}
	print5(n);
}

void newtonF()
{
	vector<double> n;
	vector<vector<double>> v;
	for (int i = 0; i < x1.size(); i++)
		v.push_back(newtonM(i, 2));
	for (int i = 0; i < x1.size(); i++)
	{
		double s = 0;
		for (int j = 0; j < x1.size(); j++)
		{
			s += newtonKf(j) * v[j][i];
		}
		n.push_back(s);
	}
	print4(n);
}

vector<double> LU(vector<double>& c, vector<vector<double>>& a, int nn)
{
	vector<vector<double>> matrix = a;
	vector<double> b = c;
	vector<vector<double>> u;
	for (int i = 0; i < nn; i++) {
		vector<double> v;
		for (int j = 0; j < nn; j++)
			v.push_back(0);
		u.push_back(v);
	}
	vector<vector<double>> l;
	for (int i = 0; i < nn; i++) {
		vector<double> v;
		for (int j = 0; j < nn; j++)
		{
			if (i == j) v.push_back(1);
			else v.push_back(0);
		}
		l.push_back(v);
	}

	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < nn; j++)
		{
			if (i <= j)
			{
				double lu = 0;
				for (int k = 0; k < i; k++)
					lu += l[i][k] * u[k][j];
				u[i][j] = matrix[i][j] - lu;
			}
			else if (i > j)
			{
				double lu = 0;
				for (int k = 0; k < j; k++)
					lu += l[i][k] * u[k][j];
				l[i][j] = (matrix[i][j] - lu) / u[j][j];
			}
		}
	}
	vector<double> y(nn);
	for (int k = 0; k < nn; k++)
	{
		double ly = 0;
		for (int j = 0; j < k; j++)
			ly += l[k][j] * y[j];
		y[k] = b[k] - ly;
	}
	vector<double> x(nn);
	for (int k = nn - 1; k > -1; k--)
	{
		double ux = 0;
		for (int j = k + 1; j < nn; j++)
			ux += u[k][j] * x[j];
		x[k] = (y[k] - ux) / u[k][k];
	}
	return x;
}

void hermit()
{
	vector<double> a = LU(Hy, Hx, Hy.size());
	print10(a);
}

int main()
{
	cout << "Lagr: "; lagr();
	cout << endl;
	cout << "Lagr for f(x): ";  lagrF();
	cout << endl;
	cout << "Newton: "; newton();
	cout << endl;
	cout << "Newton for f(x): "; newtonF();
	cout << endl;
	cout << "Hermin: "; hermit();
	return 0;
}