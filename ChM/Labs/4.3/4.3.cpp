#include <iostream>
#include <vector>
#include <iomanip>

std::vector<double> operator+(const std::vector<double>& a, const std::vector<double>& b)
{
	std::vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] + b[i];
	return (c);
}
std::vector<std::vector<double>>operator+(std::vector<std::vector<double>>a, std::vector<std::vector<double>> b)
{
	int nn = a.size();
	std::vector<std::vector<double>> ab;
	for (int i = 0; i < nn; i++)
	{
		std::vector<double> v(nn);
		for (int j = 0; j < nn; j++)
		{
			v[j] = a[i][j] + b[i][j];
		}
		ab.push_back(v);
	}
	return ab;
}
std::vector<double> operator-(const std::vector<double>& a, const std::vector<double>& b)
{
	std::vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] - b[i];
	return c;
}
std::vector<std::vector<double>>operator-(std::vector<std::vector<double>>a)
{
	std::vector<std::vector<double>> b;
	for (int i = 0; i < a.size(); i++)
	{
		std::vector<double> v(a.size());
		for (int j = 0; j < a.size(); j++)
		{
			v[j] = -a[i][j];
		}
		b.push_back(v);
	}
	return b;
}
std::vector<std::vector<double>> operator*(double k, std::vector<std::vector<double>> a)
{
	int n = a.size();
	std::vector<std::vector<double>> ka;
	for (int i = 0; i < n; i++)
	{
		std::vector<double> v(n);
		for (int j = 0; j < n; j++)
		{
			v[j] = k * a[i][j];
		}
		ka.push_back(v);
	}
	return ka;
}
std::vector<std::vector<double>> operator*(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b)
{
	int nn = a.size();
	std::vector<std::vector<double>> ab;
	for (int i = 0; i < nn; i++)
	{
		std::vector<double> v(nn);
		for (int l = 0; l < nn; l++)
		{
			double s = 0;
			for (int j = 0; j < nn; j++)
			{
				s += a[i][j] * b[j][l];
			}
			v[l] = s;
		}
		ab.push_back(v);
	}
	return ab;
}
std::vector<double> operator*(std::vector<std::vector<double>> a, std::vector<double> x)
{
	int nn = x.size();
	std::vector<double> ax(nn);
	for (int i = 0; i < nn; i++)
	{
		double s = 0;
		for (int j = 0; j < nn; j++)
		{
			s += a[i][j] * x[j];
		}
		ax[i] = s;
	}
	return ax;
}
std::vector<std::vector<double>>UnitMatrix(int nn)
{
	std::vector<std::vector<double>> e;
	for (int i = 0; i < nn; i++)
	{
		std::vector<double> v(nn);
		v[i] = 1;
		e.push_back(v);
	}
	return e;
}
std::vector<std::vector<double>> InverseMatrix(std::vector<std::vector<double>> a)
{
	std::vector<std::vector<double>> matrix = a;
	int nn = a.size();
	std::vector<std::vector<double>> I = UnitMatrix(nn);
	double t;
	for (int k = 0; k < nn; k++)
	{
		t = matrix[k][k];
		for (int j = 0; j < nn; j++)
		{
			matrix[k][j] /= t;
			I[k][j] /= t;
		}
		for (int i = k + 1; i < nn; i++)
		{
			t = matrix[i][k];
			for (int j = 0; j < nn; j++)
			{
				matrix[i][j] -= matrix[k][j] * t;
				I[i][j] -= I[k][j] * t;
			}
		}
	}
	for (int k = nn - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			t = matrix[i][k];

			for (int j = 0; j < nn; j++)
			{
				matrix[i][j] -= matrix[k][j] * t;
				I[i][j] -= I[k][j] * t;
			}
		}
	}
	return I;
}
double Norm(std::vector<double> x, std::vector<double> xk)
{
	int nn = x.size();
	double norm = 0;
	for (int i = 0; i < nn; i++)
		norm += pow((x[i] - xk[i]), 2);
	norm = sqrt(norm);
	return norm;
}
std::vector<double> Zeidel(std::vector<std::vector<double>> a, std::vector<double> b)
{
	int nn = b.size();
	std::vector<std::vector<double>>B;
	std::vector<double> c(nn);
	std::vector<std::vector<double>>L;
	std::vector<std::vector<double>>D;
	std::vector<std::vector<double>>R;
	for (int i = 0; i < nn; i++)
	{
		std::vector<double> l(nn);
		std::vector<double> d(nn);
		std::vector<double> r(nn);
		for (int j = 0; j < nn; j++)
		{
			if (j < i) l[j] = a[i][j];
			if (j == i) d[j] = a[i][j];
			if (j > i) r[j] = a[i][j];
		}
		L.push_back(l);
		D.push_back(d);
		R.push_back(r);
	}
	B = -InverseMatrix(L + D) * R;
	c = InverseMatrix(L + D) * b;
	std::cout << "zeidel: ";
	for (int i = 0; i < c.size(); i++)
		std::cout << std::setw(10) << c[i];
	std::cout << std::endl;
	std::vector<double> x(nn);
	std::vector<double> xk(nn);
	do {
		x = B * xk + c;
	} while (Norm(x, xk) > 1e-3);
	std::cout << "zeidel: ";
	for (int i = 0; i < x.size(); i++)
		std::cout << std::setw(10) << x[i];
	std::cout << std::endl;
	return x;
}
std::vector<double> Gauss(std::vector<double>& c, std::vector<std::vector<double>>& a, int nn)
{
	std::vector<std::vector<double>> matrix = a;
	std::vector<double> b = c;
	for (int k = 0; k < nn; k++)
	{
		for (int i = k + 1; i < nn; i++)
		{
			double t = matrix[i][k] / matrix[k][k];
			b[i] -= t * b[k];
			for (int j = k; j < nn; j++)
				matrix[i][j] -= t * matrix[k][j];
		}
	}
	std::vector<double> x(nn);
	x[nn - 1] = b[nn - 1] / matrix[nn - 1][nn - 1];

	for (int k = nn - 2; k >= 0; k--)
	{
		double s = 0;
		for (int j = k + 1; j <= nn - 1; j++)
			s += matrix[k][j] * x[j];
		x[k] = (b[k] - s) / matrix[k][k];
	}
	return x;
}
std::vector<double> ProstIter(std::vector<double>& c, std::vector<std::vector<double>>& a, int nn)
{
	std::vector<std::vector<double>> S = 0.5 * InverseMatrix(a);
	std::vector<double> x(nn);
	std::vector<double> xk(nn);
	do {
		xk = x;
		x = xk - S * (a * xk - c);
	} while (Norm(x, xk) > 1e-8);
	return x;
}
std::vector<double> Progonka(std::vector<double> b, std::vector<double> c, std::vector<double> d, std::vector<double> r)
{
	int n = r.size();
	std::vector<double> s(n);
	s[0] = -d[0] / c[0];
	std::vector<double> l(n);
	l[0] = r[0] / c[0];
	for (int i = 1; i < n; i++)
	{
		s[i] = -d[i] / (c[i] + b[i] * s[i - 1]);
		l[i] = (r[i] - b[i] * l[i - 1]) / (c[i] + b[i] * s[i - 1]);
	}
	std::vector<double> x(n);
	x[n - 1] = l[n - 1];
	for (int i = n - 2; i >= 0; i--)
		x[i] = s[i] * x[i + 1] + l[i];
	return x;
}

const int n = 3, N = 10;
double a = 1, b = 2, alfa = 1, beta = -3, gamma = 2, delta = 1,
A = 1, B = -1;
double d = (B * alfa + B * a * beta - A * delta - A * gamma * b) / (-delta * beta - gamma * b * beta + alfa * gamma + a * beta * gamma);
double c = (A - beta * d) / (alfa + a * beta);

//u''+p(x)u'+q(x)u=f(x)
//alfa*u'(a)+beta*u(a)=A
//delta*u'(b)+gamma*u(b)=B
double p(double x)
{
	return -(x + 3) / x;
}
double q(double x)
{
	return -(2 * x + 3) / x;
}
double f(double x)
{
	return x * x;
}

double fv(double x, double u, double du)
{
	return f(x) - p(x) * du - q(x) * u;
}
double fw(double x, double u, double du)
{
	return -p(x) * du - q(x) * u;
}
std::pair<std::vector<double>, std::vector<double>> RK(double h, std::vector<double> u, std::vector<double> du,
	std::vector<double> x, double(*op)(double,double,double))
{
	for (int i = 0; i < x.size(); i++)
	{
		double phi1 = h * du[i];
		double psi1 = h * op(x[i], u[i], du[i]);
		double phi2 = h * (du[i] + psi1 / 2.);
		double psi2 = h * op(x[i] + h / 2., u[i] + phi1 / 2., du[i] + psi1 / 2.);
		double phi3 = h * (du[i] + psi2 / 2.);
		double psi3 = h * op(x[i] + h / 2., u[i] + phi2 / 2., du[i] + psi2 / 2.);
		double phi4 = h * (du[i] + psi3);
		double psi4 = h * op(x[i] + h, u[i] + phi3, du[i] + psi3);
		u.push_back(u[i] + 1 / 6. * (phi1 + 2 * phi2 + 2 * phi3 + phi4));
		du.push_back(du[i] + 1 / 6. * (psi1 + 2 * psi2 + 2 * psi3 + psi4));
	}
	return std::make_pair(u, du);
}
void strelba()
{
	double h = (b - a) / N;
	std::vector<double> x;
	for (double i = a+h; i <= b+1e-3; i += h)
		x.push_back(i);
	std::cout << "x: ";
	for (int i = 0; i < x.size(); i++)
		std::cout << std::setw(10) << x[i];
	std::cout << std::endl;
	std::vector<double> v = { 0 };
	std::vector<double> dv = { A / alfa };
	//RK(h, v, dv, x, fv);
	v = RK(h, v, dv, x, fv).first;
	std::cout << "v: ";
	for (int i = 0; i < v.size(); i++)
		std::cout << std::setw(10) << v[i];
	std::cout << std::endl;
	dv = RK(h, v, dv, x, fv).second;
	std::cout << "dv: ";
	for (int i = 0; i < dv.size(); i++)
		std::cout << std::setw(10) << dv[i];
	std::cout << std::endl;
	std::vector<double> w = { -alfa/beta };
	std::vector<double> dw = { 1 };
	//RK(h, w, dw, x, fw);
	w = RK(h, w, dw, x, fw).first; 
	dw = RK(h, w, dw, x, fw).second;
	double c = (B - delta * dv[dv.size()-1] - gamma * v[v.size() - 1]) / (delta * dw[dw.size() - 1] + gamma * w[w.size() - 1]);
	std::vector<double> u;
	for (int i = 0; i < v.size(); i++)
		u.push_back(v[i] + c * w[i]);
	std::cout << "strelba: ";
	for (int i = 0; i < u.size(); i++)
		std::cout << std::setw(10) << u[i];
	std::cout << std::endl;
}
double Pi(int i)
{
	return (-(b - a) * (delta * (i + 2) + gamma * (b - a))) / (delta * (i + 1) + gamma * (b - a));
}
double Phi(double x, int i)
{
	return Pi(i) * pow(x - a, i + 1) + pow(x - a, i + 2);
}
double Phi0(double x, int i)
{
	return c * x + d;
}
double dPhi(double x, int i)
{
	return (i + 1) * Pi(i) * pow(x - a, i) + (i + 2) * pow(x - a, i + 1);
}
double dPhi0(double x, int i)
{
	return c;
}
double ddPhi(double x, int i)
{
	return (i + 1) * i * Pi(i) * pow(x - a, i - 1) + (i + 2) * (i + 1) * pow(x - a, i);
}
double ddPhi0(double x, int i)
{
	return 0;
}

void kollok()
{
	double h = (b - a) / N;
	std::vector<double> x;
	for (double i = a; i <= b+1e-3; i += h)
		x.push_back(i);
	std::vector<std::vector<double>> matr(N);
	std::vector<double> vec;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matr[i].push_back(ddPhi(x[i], j+1) + p(x[i]) * dPhi(x[i], j+1) + q(x[i]) * Phi(x[i], j+1));
		}
		vec.push_back(f(x[i]) - ddPhi0(x[i],0) - p(x[i]) * dPhi0(x[i],0) - q(x[i]) * Phi0(x[i],0));
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << std::setw(10) << matr[i][j];
		std::cout << std::endl;
	}
				
	std::vector<double> C = Gauss(vec, matr, N);
	std::vector<double> y;
	for (int i = 0; i < N; i++)
	{
		double s = 0;
		for (int j = 0; j < N; j++)
			s += C[j] * Phi(x[i], j+1);
		y.push_back(Phi0(x[i],0) + s);
	}
	std::cout << "kollokat: ";
	for (int i = 0; i < y.size(); i++)
		std::cout << std::setw(10) << y[i];
	std::cout << std::endl;
}

double La(double x, int i)
{
	return ddPhi(x, i) + p(x) * dPhi(x, i) + q(x) * Phi(x, i);
}
double Lb(double x, int i)
{
	return f(x) - ddPhi0(x, i) + p(x) * dPhi0(x, i) + q(x) * Phi0(x, i);
}

double simpson(double h, double(*l)(double,int), int i, int j)
{
	double s = h / 6 * (l(a,i)*Phi(a,j) + l(b, i) * Phi(b, j));
	for (double k = a + h; k <= b - h; k += h)
		s += h / 6 * 2 * l(k, i) * Phi(k, j);
	for (double k = a + h; k <= b; k += h)
		s += h / 6 * 4 * l((k + k - h) / 2, i) * Phi((k + k - h) / 2, j); 
	return s;
}
void galerkin()
{
	double h = (b - a) / N;
	std::vector<double> x;
	for (double i = a; i <= b+1e-3; i += h)
		x.push_back(i);
	// L[u] = u"(x) + p(x)u'(x) + q(x)u(x) = f(x)
	// aij = phij"(xi) + p(xi)phij'(xi) + q(xi)phij(xi)
	// bi = f(xi) - phi0"(xi) - p(xi)phi0'(xi) - q(xi)phi0(xi)
	std::vector<std::vector<double>> matr(N);
	std::vector<double> vec;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			matr[i].push_back(simpson(h,La,i+1,j+1));
		}
		vec.push_back(simpson(h,Lb,0,i+1));
	}
	//std::cout << "vek: ";
	//for (int i = 0; i < vec.size(); i++)
		//std::cout << std::setw(10) << vec[i];
	//std::cout << std::endl;
	std::vector<double> C = Gauss(vec, matr, N);
	std::vector<double> y;
	for (int i = 0; i < N; i++)
	{
		double s = 0;
		for (int j = 0; j < N; j++)
			s += C[j] * Phi(x[i], j + 1);
		y.push_back(Phi0(x[i], 0) + s);
	}
	std::cout << "galerkin: ";
	for (int i = 0; i < y.size(); i++)
		std::cout << std::setw(10) << y[i];
	std::cout << std::endl;
}
void raznMeth()
{
	double h = (b - a) / N;
	std::vector<double> x;
	for (double i = a; i <= b+1e-3; i += h)
		x.push_back(i);
	std::vector<double> c, d, b, r;
	c.push_back(beta * h - alfa);
	d.push_back(alfa);
	b.push_back(0);
	r.push_back(A * h);
	for (int i = 1; i < x.size() - 1; i++)
	{
		b.push_back(2 - p(x[i]) * h);
		c.push_back(-4 + 2 * h * h * q(x[i]));
		d.push_back(2 + h * p(x[i]));
		r.push_back(2 * h * h * f(x[i]));
	}
	b.push_back(-beta);
	c.push_back(gamma * h + delta);
	d.push_back(0);
	r.push_back(B * h);
	std::vector<double> y = Progonka(b, c, d, r);
	std::cout << "raznMeth: ";
	for (int i = 0; i < y.size(); i++)
		std::cout << std::setw(10) << y[i];
	std::cout << std::endl;
}
int main()
{
	strelba();
	kollok();
	galerkin();
	raznMeth();
	return 0;
}