#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

int n = 3;
double a = 0.2 * (n + 6); //1.8
double b = 0.3 * (n + 6); //2.7
double eps = 1e-3;

double f(double x)
{
	return 1 / (x + sin(0.1 * n * x));
}
double diff(double x)
{
	return -(1 + 0.1 * n * cos(0.1 * n * x)) / pow(x + sin(0.1 * n * x), 2);
}
double diff2(double x)
{
	return 0.3 * 0.3 * sin(0.3 * x) / pow(x + sin(0.1 * n * x), 2) +
		2 * pow(0.3 * cos(0.3 * x) + 1, 2) / pow(x + sin(0.1 * n * x), 3);
}
double diff4(double x)
{
	return 0.0486 * pow(sin(0.3 * x), 2) / pow(x + sin(0.1 * n * x), 3) -
		0.0081 * sin(0.3 * x) / pow(x + sin(0.1 * n * x), 2) +
		24 * pow(0.3 * cos(0.3 * x) + 1, 4) / pow(x + sin(0.1 * n * x), 5) +
		3.24 * sin(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 2) / pow(x + sin(0.1 * n * x), 4) -
		0.216 * cos(0.3 * x) * (0.3 * cos(0.3 * x) + 1) / pow(x + sin(0.1 * n * x), 3);
}
double diff8(double x)
{
	return (0.165337 * pow(sin(0.3 * x), 4)) / pow(x + sin(0.3 * x), 5) - (0.0826686 * pow(sin(0.3 * x), 3) )/ pow(x + sin(0.3 * x), 4) +
		(0.00826686 * pow(sin(0.3 * x), 2)) / pow(x + sin(0.3 * x), 3) - (0.00006561 * sin(0.3 * x)) / pow(x + sin(0.3 * x), 2) +
			(4.89888 * pow(cos(0.3 * x), 2) * pow(0.3 * cos(0.3 * x) + 1, 2) / pow(x + sin(0.3 * x), 5) -
				(0.00734832 * pow(cos(0.3 * x), 2)) / pow(x + sin(0.3 * x), 3) + (0.110225 * sin(0.3 * x) * pow(cos(0.3 * x), 2)) / pow(x + sin(0.3 * x), 4) +
					(36.7416 * pow(sin(0.3 * x), 3) * pow(0.3 * cos(0.3 * x) + 1, 2)) / pow(x + sin(0.3 * x), 6) +
						(1224.72 * pow(sin(0.3 * x), 2) * pow(0.3 *cos(0.3 * x) + 1, 4)) / pow(x + sin(0.3 * x), 7) -
							(7.34832 * pow(sin(0.3 * x), 2) * pow(0.3 * cos(0.3 * x) + 1, 2) )/ pow(x + sin(0.3 * x), 5) -
								(4.40899 * pow(sin(0.3 * x), 2) * cos(0.3 * x) * (0.3 * cos(0.3 * x) + 1)) / pow(x + sin(0.3 * x), 5) +
								(40320 * pow(0.3 * cos(0.3 * x) + 1, 8)) / pow(x + sin(0.3 * x), 9) +
									(12700.8 * sin(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 6)) / pow(x + sin(0.3 * x), 8) -
										(1088.64 * cos(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 5)) / pow(x + sin(0.3 * x), 7) -
											(68.04 * sin(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 4)) / pow(x + sin(0.3 * x), 6) +
												(3.26592 * cos(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 3)) / pow(x + sin(0.3 * x), 5) -
													(163.296 * sin(0.3 * x) * cos(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 3) )/ pow(x + sin(0.3 * x), 6) +
														(0.122472 * sin(0.3 * x) * pow(0.3 * cos(0.3 * x) + 1, 2)) / pow(x + sin(0.3 * x), 4) -
															(0.0034992 * cos(0.3 * x) * (0.3 * cos(0.3 * x) + 1)) / pow(x + sin(0.3 * x), 3) +
															(0.587866 * sin(0.3 * x) * cos(0.3 * x) * (0.3 * cos(0.3 * x) + 1)) / pow(x + sin(0.3 * x), 4));
}

int N1 = pow(b - a, 2) * abs(diff(a)) / (2 * eps);
double h1 = (b - a) / N1;

int N2 = ceil(sqrt((pow(b - a, 3) * abs(diff2(a))) / (24 * eps)));
double h2 = (b - a) / N2;

double df(double x)
{
	double h = 0.01;
	return (f(x + h) - f(x - h)) / (2 * h);
}
double df2(double x)
{
	double h = 0.01;
	return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

void leftPr()
{
	double s = 0;
	int k = 0;
	double h = h1;
	for (double i = a; i <= b-h; i += h)
	{
		s += f(i) * h;
		k++;
	}
	cout << endl << "left pr:" << s << "    " << k;
}

void rightPr()
{
	double s = 0;
	int k = 0;
	double h = h1;
	for (double i = a + h; i <= b; i += h)
	{
		s += f(i) * h;
		k++;
		///cout << i << "  ";
	}
	cout << endl << "right pr: " << s << "   " << k;
}

void avrPr()
{
	double s = 0;
	double h = h2;
	int k = 0;
	for (double i = a + h; i <= b; i += h)
	{
		s += f((i + i - h) / 2) * h; k++;
	}
	printf("\navr pr: %.8le it: %d", s, k);
}

int N3 = ceil(sqrt((pow(b - a, 3) * abs(diff2(a))) / (12 * eps)));
double h3 = (b - a) / N3;

void trap()
{
	double h = h3;
	double s = h / 2 * (f(a) + f(b));
	for (double i = a + h; i <= b - h; i += h)
		s += h * f(i);
	printf("\ntrap: %.8le", s);
}

int N4 = ceil(pow((pow(b - a, 5) * abs(diff4(a))) / (2880 * eps),1/4.0));
double h4 = (b - a) / N4;

void simpson()
{
	double h = h4;
	double s = h / 6 * (f(a) + f(b));
	for (double i = a + h; i <= b - h; i += h)
		s += h / 6 * 2 * f(i);
	for (double i = a + h; i <= b; i += h)
		s += h / 6 * 4 * f((i + i - h) / 2);
	cout << endl << "simpson: " << s << "   " << N4;
}

double simpson(double h)
{
	double s = h / 6 * (f(a) + f(b));
	for (double i = a + h; i <= b - h; i += h)
		s += h / 6 * 2 * f(i);
	for (double i = a + h; i <= b; i += h)
		s += h / 6 * 4 * f((i + i - h) / 2);
	return s;
}

int N5 = 4; double h5 = (b - a) / N5;
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
vector<double>yz;

vector<double> Pch(int i)
{
	vector<double>v = yz;
	v.erase(v.begin() + i);
	vector<double> p = { 1, -v[0] - v[1] - v[2] - v[3],
		(-v[0] - v[1]) * (-v[2] - v[3]) + (-v[0]) * (-v[1]) + (-v[2]) * (-v[3]),
		(-v[0] - v[1]) * (-v[2]) * (-v[3]) + (-v[2] - v[3]) * (-v[0]) * (-v[1]),
		(-v[0]) * (-v[1]) * (-v[2]) * (-v[3]) };
	return p;
}
double Pz(int i)
{
	double p = 1;
	for (int j = 0; j < yz.size(); j++)
	{
		if (j != i)
			p *= (yz[i] - yz[j]);
	}
	return p;
}
vector<double> lagr()
{
	
	vector<double>l;
	vector<double>v;
	for (int i = 0; i < yz.size(); i++)
		v.push_back(f(yz[i]) / Pz(i));
	for (int i = 0; i < yz.size(); i++)
	{
		double s = 0;
		for (int j = 0; j < yz.size(); j++)
			s += v[j] * Pch(j)[i];
		l.push_back(s);
	}
	//print5(l);
	return l;
}
double LA(double x)
{
	vector<double> l = lagr();
	double rez = 0;
	for (int i = 0; i < l.size(); i++)
	{
		rez += l[i] * pow(x, l.size() - i - 1);
	}
	return rez;//l[0]*pow(x,4)+l[1]*pow(x,3)+l[2]*pow(x,2)+l[3]*x+l[4];
}
void interpol()
{
	//double s = 0;
	double h = h3;
	double s = h / 2 * (LA(a) + LA(b));
	for (double i = a + h; i <= b - h + 1e-3; i += h)
		s += h * LA(i);
	cout << "\ninterpol: " << s;
}


int N6 = 4;
double P4(double x)
{
	//Pn(x) = 1/(2^n*n!)*((x^2-1)^n)^(n)
	return 4.375 * pow(x, 4) - 3.75 * pow(x, 2) + 0.375;
}
double P4Dif(double x)
{
	return 4.375 * 4 * pow(x, 3) - 3.75 * 2 * x;
}
double NR(double i)
{
	double x = i;
	do {
		x = x - P4(x) / P4Dif(x);
	} while (abs(P4(x)) > eps);
	//cout << "NR: x = " << x << endl;
	return x;
}
vector<double> T()
{
	vector<double> t;
	t.push_back(NR(-1));
	t.push_back(NR(-0.5));
	t.push_back(NR(0.5));
	t.push_back(NR(1));
	return t;
}
vector<double>X()
{
	vector<double> x;
	//x.push_back(a);
	for (int i = 0; i < N6; i++)
		x.push_back((b - a) / 2 * T()[i] + (b + a) / 2);
	return x;
}
double w(double x)
{
	double p = 1;
	double h = h3;
	for (double i = a; i <= b+1e-3; i += h)
		if (x != i)
			p *= (x - i);
	return p;
}
double WforDif(double x)
{
	double p = 1;
	double h = h3;
	for (double i = a; i <= b+1e-3; i += h)
		p *= (x - i);
	return p;
}
double difw(double x)
{
	double h = 0.01;
	return (WforDif(x + h) - WforDif(x - h)) / (2 * h);
}
double difw2(double x)
{
	vector<double> i(6);
	double h = h3;
	for (double j = a; j <= b + 1e-3; j += h)
		i.push_back(j);
	return 6 * pow(x, 5) - 5 * pow(x, 4) * (i[0] + i[1] + i[2] + i[3] + i[4] + i[5]) +
		4 * pow(x, 3) * (i[0] * i[1] + i[0] * i[2] + i[0] * i[3] + i[0] * i[4] + i[0] * i[5] +
			i[1] * i[2] + i[1] * i[3] + i[1] * i[4] + i[1] * i[5] + i[2] * i[3] + i[2] * i[4] + i[2] * i[5] +
			i[3] * i[4] + i[3] * i[5] + i[4] * i[5]) -
		3 * pow(x, 2) * (i[0] * i[1] * i[2] + i[0] * i[1] * i[3] + i[0] * i[1] * i[4] + i[0] * i[1] * i[5] +
			i[0] * i[2] * i[3] + i[0] * i[2] * i[4] + i[0] * i[2] * i[5] + i[0] * i[3] * i[4] + i[0] * i[3] * i[5] +
			i[0] * i[4] * i[5] + i[1] * i[2] * i[3] + i[1] * i[2] * i[4] + i[1] * i[2] * i[5] + i[1] * i[3] * i[4] + i[1] * i[3] * i[5] +
			i[1] * i[4] * i[5] + i[2] * i[3] * i[4] + i[2] * i[3] * i[5] + i[2] * i[4] * i[5] + i[3] * i[4] * i[5]) +
		2 * x * (i[0] * i[1] * i[2] * i[3] + i[0] * i[1] * i[2] * i[4] + i[0] * i[1] * i[2] * i[5] +
			i[0] * i[2] * i[3] * i[4] + i[0] * i[2] * i[3] * i[5] + i[0] * i[3] * i[4] * i[5] +
			i[1] * i[2] * i[3] * i[4] + i[1] * i[2] * i[3] * i[5] + i[1] * i[3] * i[4] * i[5] +
			i[2] * i[3] * i[4] * i[5]) -
		(i[0] * i[1] * i[2] * i[3] * i[4] + i[0] * i[1] * i[2] * i[3] * i[5] + i[1] * i[2] * i[3] * i[4] * i[5]);

}
double Cf(double x, double xi)
{
	return w(x) / difw2(xi);
}
double C(double x)
{
	double h = h3;
	double c = h / 2 * (Cf(a,x) + Cf(b,x));
	for (double i = a + h; i <= b - h + 1e-3; i += h)
		c += h * Cf(i,x);
	return c;
}
void gauss()
{ //trap
	double s = 0;
	for (double i = 0; i < X().size(); i++)
	{
		s += C(X()[i]) * f(X()[i]);
		cout << C(X()[i])  << "   ";
	}
	cout << "\ngauss: " << s;
}

void splain()
{
	double N = 6;
	double h = (b - a) / N;
	double s = 0;
	s += 5 * h / 12 * (f(a) + f(b)) + 13 * h / 12 * (f(a + h) + f(b - h)) + 
		pow(h, 3) / 72 * (2 * diff(a) + diff(a + h) + diff(b - h) + 2 * diff(b));
	for (double x = a + 2 * h; x <= b - 2 * h; x += h)
		s += h * f(x);
	cout << "\nsplain: " << s;
}

void Runge_Romberg()
{
	double h = h4;
	double Yh = simpson(h);
	h = h / 2;
	double Yh2 = simpson(h);
	double del = (Yh2 - Yh) / (pow(2, 4) - 1);
	int it = 0;
	while (abs(del) > 1e-8)
	{
		h = h / 2;
		Yh = Yh2;
		Yh2 = simpson(h);
		del= (Yh2 - Yh) / (pow(2, 4) - 1);
		it++;
	}
	printf("\nRunge-Romberg: %.8le, it: %d", Yh2, it);
}

int main()
{
	cout << difw2(a);
	//cout << endl << diff(a) << "  " << diff(b);
	//cout << endl << diff2(a) << "  " << diff2(b);
	//cout << endl << df(a) << "  " << df(b); 
	//cout << endl << df2(a) << "  " << df2(b);
	//cout << endl << diff4(a) << "  " << diff4(b);
	//cout << endl << w(b);
	leftPr();
	rightPr();
	avrPr();
	trap();
	simpson();
	cout << endl << a << " " << a+h3 << " " << a+2*h3 << " " << a+3*h3 << " " << a+4*h3 << " " <<a+5*h3<< endl;
	for (double i = a; i <= b+1e-3; i += h5)
	{
		yz.push_back(i);
		//cout << i << " ";
	}
	//cout << endl << yz.size();
	cout << endl;  print5(lagr());
	interpol();
	cout << endl;
	gauss();
	cout << endl;
	for (int i = 0; i < X().size(); i++)
		cout << X()[i] << "  ";
	//cout << endl;
	//for (int i = 0; i < T().size(); i++)
	//	cout << T()[i] << "  ";
	splain();
	Runge_Romberg();
	return 0;
}