#pragma once
#include "Matrix.h"
#include "math.h"

using namespace std;

vector<vector<double>> E()
{
	vector<vector<double>> e;
	for (int i = 0; i < n; i++)
	{
		vector<double> v(n);
		v[i] = 1;
		e.push_back(v);
	}
	return e;
}
vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
	vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] + b[i];
	return (c);
}
vector<vector<double>>operator+(vector<vector<double>>a, vector<vector<double>> b)
{
	int nn = a.size();
	vector<vector<double>> ab;
	for (int i = 0; i < nn; i++)
	{
		vector<double> v(nn);
		for (int j = 0; j < nn; j++)
		{
			v[j] = a[i][j] + b[i][j];
		}
		ab.push_back(v);
	}
	return ab;
}
vector<double> operator+=(vector<double>& a, vector<double>& b)
{
	for (int i = 0; i < a.size(); i++)
		a[i] += b[i];
	return a;
}
vector<double> operator-(const vector<double>& a, const vector<double>& b)
{
	vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] - b[i];
	return c;
}
vector<vector<double>>operator-(vector<vector<double>>a)
{
	vector<vector<double>> b;
	for (int i = 0; i < a.size(); i++)
	{
		vector<double> v(a.size());
		for (int j = 0; j < a.size(); j++)
		{
			v[j] = -a[i][j];
		}
		b.push_back(v);
	}
	return b;
}
vector<double> operator-=(vector<double>& a, vector<double>& b)
{
	for (int i = 0; i < a.size(); i++)
		a[i] -= b[i];
	return a;
}
vector<double> operator/(vector<double> a, double b)
{
	vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] / b;
	return c;
}
vector<double> operator*(double k, vector<double>x)
{
	vector<double> kx(x.size());
	for (int i = 0; i < x.size(); i++)
		kx[i] = k * x[i];
	return kx;
}
vector<vector<double>> operator*(double k, vector<vector<double>> a)
{
	vector<vector<double>> ka;
	for (int i = 0; i < n; i++)
	{
		vector<double> v(n);
		for (int j = 0; j < n; j++)
		{
			v[j] = k * a[i][j];
		}
		ka.push_back(v);
	}
	return ka;
}
vector<vector<double>> operator*(vector<vector<double>> a, vector<vector<double>> b)
{
	int nn = a.size();
	vector<vector<double>> ab;
	for (int i = 0; i < nn; i++)
	{
		vector<double> v(nn);
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
vector<double> operator*(Matrix& a, vector<double> x)
{
	vector<double> ax(n);
	for (int i = 0; i < n; i++)
	{
		double s = 0;
		for (int j = 0; j < n; j++)
		{
			s += a.getMatrix(j, i) * x[j];
		}
		ax[i] = s;
	}
	return ax;
}
vector<double> operator*(vector<vector<double>> a, vector<double> x)
{
	int nn = x.size();
	vector<double> ax(nn);
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

class Solver
{
public:
	Solver() {};
	~Solver() {};

	void print(vector<vector<double>> matrix)
	{
		cout << "\nMatrix: " << endl;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
				cout << setw(10) << matrix[i][j];
			cout << endl;
		}
	}

	vector<vector<double>>UnitMatrix()
	{
		vector<vector<double>> e;
		for (int i = 0; i < n; i++)
		{
			vector<double> v(n);
			v[i] = 1;
			e.push_back(v);
		}
		return e;
	}
	vector<vector<double>>UnitMatrix(int nn)
	{
		vector<vector<double>> e;
		for (int i = 0; i < nn; i++)
		{
			vector<double> v(nn);
			v[i] = 1;
			e.push_back(v);
		}
		return e;
	}

	vector<vector<double>> InverseMatrix(Matrix& a)
	{
		vector<vector<double>> matrix = a.getMatrix();
		vector<vector<double>> I = UnitMatrix();
		double t;
		for (int k = 0; k < n; k++)
		{
			t = matrix[k][k];
			for (int j = 0; j < n; j++)
			{
				matrix[k][j] /= t;
				I[k][j] /= t;
			}
			for (int i = k + 1; i < n; i++)
			{
				t = matrix[i][k];
				for (int j = 0; j < n; j++)
				{
					matrix[i][j] -= matrix[k][j] * t;
					I[i][j] -= I[k][j] * t;
				}
			}
		}
		for (int k = n - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				t = matrix[i][k];

				for (int j = 0; j < n; j++)
				{
					matrix[i][j] -= matrix[k][j] * t;
					I[i][j] -= I[k][j] * t;
				}
			}
		}
		//a.print(I);
		//a.print(matrix);
		return I;
	}
	vector<vector<double>> InverseMatrix(vector<vector<double>> a)
	{
		vector<vector<double>> matrix = a;
		int nn = a.size();
		vector<vector<double>> I = UnitMatrix(nn);
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

	int Sign(double val)
	{
		if (val == 0.) return 0;
		if (val > 0.) return 1;
		else return -1;
	}

	double Scalar(vector<double> a, vector<double> b)
	{
		double s = 0;
		for (int i = 0; i < a.size(); i++)
			s += a[i] * b[i];
		return s;
	}
	double Norm(vector<double> a)
	{
		return sqrt(Scalar(a, a));
	}
	double Norm(vector<double> x, vector<double> xk)
	{
		int nn = x.size();
		double norm = 0;
		for (int i = 0; i < nn; i++)
			norm += pow((x[i] - xk[i]), 2);
		norm = sqrt(norm);
		return norm;
	}
	
	void Gauss(Matrix& a)
	{
		cout << "\nGauss: ";
		vector<vector<double>> matrix = a.getMatrix();
		vector<double> b = a.getB();
		for (int k = 0; k < n; k++)
		{
			for (int i = k + 1; i < n; i++)
			{
				double t = matrix[i][k] / matrix[k][k];
				b[i] -= t * b[k];
				for (int j = k; j < n; j++)
					matrix[i][j] -= t * matrix[k][j];
			}
		}
		//a.print(matrix);
		double det = 1;
		for (int i = 0; i < n; i++)
			det = det * matrix[i][i];
		cout << "det = " << det;

		vector<double> x(n);
		x[n - 1] = b[n - 1] / matrix[n - 1][n - 1];

		for (int k = n - 2; k >= 0; k--)
		{
			double s = 0;
			for (int j = k + 1; j <= n - 1; j++)
				s += matrix[k][j] * x[j];
			x[k] = (b[k] - s) / matrix[k][k];
		}
		a.print(x);
	}
	vector<double> Gauss2(vector<double>& c, vector<vector<double>>& a, int nn)
	{
		vector<vector<double>> matrix = a;
		vector<double> b = c;
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
		vector<double> x(nn);
		x[nn - 1] = b[nn - 1] / matrix[nn - 1][nn - 1];

		for (int k = nn - 2; k >= 0; k--)
		{
			double s = 0;
			for (int j = k + 1; j <= nn - 1; j++)
				s += matrix[k][j] * x[j];
			x[k] = (b[k] - s) / matrix[k][k];
		}
		for (int i = 0; i < b.size(); i++)
			cout << setw(11) << b[i];
		return x;
	}

	void Gordan_Gauss(Matrix& a)
	{
		cout << "\nGordan_Gauss: ";
		vector<vector<double>> matrix = a.getMatrix();
		vector<double> b = a.getB();

		for (int k = 0; k < n; k++)
		{
			for (int i = 0; i < n; i++)
			{
				double t = matrix[i][k] / matrix[k][k];
				if (i != k)
				{
					for (int j = k; j < n; j++)
						matrix[i][j] = -t * matrix[k][j] + matrix[i][j];
					b[i] = -t * b[k] + b[i];
				}
			}
		}
		//a.print(matrix);
		vector<double> x(n);
		for (int i = 0; i < n; i++)
			x[i] = b[i] / matrix[i][i];
		a.print(x);
	}

	void LU(Matrix& a)
	{
		cout << "\nLU: ";
		vector<vector<double>> matrix = a.getMatrix();
		vector<double> b = a.getB();
		vector<vector<double>> u;
		for (int i = 0; i < n; i++) {
			vector<double> v;
			for (int j = 0; j < n; j++)
				v.push_back(0);
			u.push_back(v);
		}
		vector<vector<double>> l;
		for (int i = 0; i < n; i++) {
			vector<double> v;
			for (int j = 0; j < n; j++)
			{
				if (i == j) v.push_back(1);
				else v.push_back(0);
			}
			l.push_back(v);
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
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
					l[i][j] = (matrix[i][j] - lu)/u[j][j];
				}
			}
		}
		vector<double> y(n);
		for (int k = 0; k < n; k++)
		{
			double ly = 0;
			for (int j = 0; j < k; j++)
				ly += l[k][j] * y[j];
			y[k] = b[k] - ly;
		}
		vector<double> x(n);
		for (int k = n - 1; k > -1; k--)
		{
			double ux = 0;
			for (int j = k + 1; j < n; j++)
				ux += u[k][j] * x[j];
			x[k] = (y[k] - ux) / u[k][k];
		}
		a.print(x);
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
			for (int j = k + 1; j < n; j++)
				ux += u[k][j] * x[j];
			x[k] = (y[k] - ux) / u[k][k];
		}
		return x;
	}

	void Holez(Matrix& a)
	{
		cout << "\nHolez: ";
		vector<int> d(n); d[0] = 1;
		vector<vector<double>> s(n);
		for (int i = 0; i < n; i++)
		{
			vector<double> v(n);
			s[i] = v;
		}

		for (int i = 0; i < n; i++)
		{
			double sd = 0;
			for (int p = 0; p < i; p++)
				sd += s[p][i] * s[p][i] * d[p];
			d[i] = Sign(a.getMatrix(i, i) - sd);
			s[i][i] = sqrt(abs(a.getMatrix(i, i) - sd));
			for (int j = i + 1; j < n; j++)
			{
				 double sds = 0;
				 for (int p = 0; p < i; p++)
					 sds += s[p][i] * d[p] * s[p][j];				
				s[i][j] = (a.getMatrix(i, j) - sds) / (d[i] * s[i][i]);
			}
			
		}
		vector<vector<double>> st;
		for (int i = 0; i < n; i++)
		{
			vector<double> v;
			for (int j = 0; j < n; j++)
				v.push_back(s[j][i]);
			st.push_back(v);
		}

		vector<double> y(n);
		for (int k = 0; k < n; k++)
		{
			double ly = 0;
			for (int j = 0; j < k; j++)
				ly += st[k][j] * y[j];
			y[k] = (a.getB(k) - ly)/st[k][k];
		}
		vector<double> x(n);
		for (int k = n - 1; k > -1; k--)
		{
			double ux = 0;
			for (int j = k + 1; j < n; j++)
				ux += s[k][j] * x[j];
			x[k] = (y[k] - ux) / s[k][k];
		}
		a.print(x);
	}

	void Ortogonal(Matrix& A)
	{
		cout << "\nOrtogonal: ";
		vector<vector<double>> a;
		for (int i = 0; i < n; i++)
		{
			vector<double> v;
			for (int j = 0; j < n; j++)
				v.push_back(A.getMatrix(i, j));
			v.push_back(-A.getB(i));
			a.push_back(v);
		}
		vector<double> a1(n + 1);
		a1[n] = 1;
		a.push_back(a1);
		vector<vector<double>> u(n + 1);
		vector<vector<double>> v(n + 1);
		for (int j = 0; j <= n; j++)
		{
			vector<double> gv(n+1);
			for (int i = 0; i <= j - 1; i++)
			{
				double g = Scalar(a[j], v[i]);
				gv = gv + g * v[i];
			}
			u[j] = a[j] - gv;
			v[j] = u[j] / Norm(u[j]);
		}
		vector<double> x(n);
		for (int i = 0; i < n; i++)
		{
			x[i] = u[n][i] / u[n][n];
		}
		A.print(x);
	}
	vector<double> Ortogonal(vector<double>& c, vector<vector<double>>& A, int nn)
	{
		vector<vector<double>> a;
		for (int i = 0; i < nn; i++)
		{
			vector<double> v;
			for (int j = 0; j < nn; j++)
				v.push_back(A[i][j]);
			v.push_back(-c[i]);
			a.push_back(v);
		}
		vector<double> a1(nn + 1);
		a1[nn] = 1;
		a.push_back(a1);
		vector<vector<double>> u(nn + 1);
		vector<vector<double>> v(nn + 1);
		for (int j = 0; j <= nn; j++)
		{
			vector<double> gv(nn + 1);
			for (int i = 0; i <= j - 1; i++)
			{
				double g = Scalar(a[j], v[i]);
				gv = gv + g * v[i];
			}
			u[j] = a[j] - gv;
			v[j] = u[j] / Norm(u[j]);
		}
		vector<double> x(nn);
		for (int i = 0; i < nn; i++)
		{
			x[i] = u[nn][i] / u[nn][nn];
		}
		return x;
	}

	void Progonka(Matrix& a)
	{
		cout << "\nProgonka: ";
		vector<double> b(n);
		b[0] = 0;
		for (int i = 1; i < n; i++)
			b[i] = a.getMatrix(i, i-1);
		vector<double> c(n);
		for (int i = 0; i < n; i++)
			c[i] = a.getMatrix(i, i);
		vector<double> d(n);
		for (int i = 0; i < n - 1; i++)
			d[i] = a.getMatrix(i, i + 1);
		d[n - 1] = 0;
		vector<double> s(n);
		s[0] = -d[0] / c[0];
		vector<double> l(n);
		l[0] = a.getB(0) / c[0];
		for (int i = 1; i < n; i++)
		{
			s[i] = -d[i]/(c[i]+b[i]*s[i-1]);
			l[i] = (a.getB(i) - b[i] * l[i - 1]) / (c[i] + b[i] * s[i - 1]);
		}
		vector<double> x(n);
		x[n - 1] = l[n - 1];
		for (int i = n - 2; i >= 0; i--)
			x[i] = s[i] * x[i + 1] + l[i];
		a.print(x);
	}

	vector<double> ProstIter(vector<double>& c, vector<vector<double>>& a, int nn)
	{
		vector<vector<double>> S = 0.5 * InverseMatrix(a);
		print(S);
		vector<double> x(nn);
		vector<double> xk(nn);
		do {
			xk = x;
			x = xk - S * (a * xk - c) ;
		} while (Norm(x, xk) > 1e-8);
		return x;
	}
	void ProstIter(Matrix& a)
	{
		cout << "\nProstIter: ";
		vector<vector<double>> S = 0.5 * InverseMatrix(a);
		vector<double> x(n);
		vector<double> xk(n);
		do {
			xk = x;
			x = xk - S * (a * xk - a.getB());
		} while (Norm(x, xk) > 1e-8);
		a.print(x);
	}

	void Jacobi(Matrix& a)
	{
		cout << "\nJacobi: ";
		//a.print(a.getMatrix() * InverseMatrix(a));
		vector<vector<double>>B;
		vector<double> c(n);
		vector<vector<double>>L;
		vector<vector<double>>D;
		vector<vector<double>>R;
		for (int i = 0; i < n; i++)
		{
			vector<double> l(n);
			vector<double> d(n);
			vector<double> r(n);
			for (int j = 0; j < n; j++)
			{
				if (j < i) l[j] = a.getMatrix(i, j);
				if (j == i) d[j] = a.getMatrix(i, j);
				if (j > i) r[j] = a.getMatrix(i, j);
			}
			L.push_back(l);
			D.push_back(d);
			R.push_back(r);
		}
		B = -InverseMatrix(D) * (L + R);
		c = InverseMatrix(D) * a.getB();
		vector<double> x(n);
		vector<double> xk(n);
		do {
			xk = x;
			x = B * xk + c;
		} while (Norm(x, xk) > 1e-3);
		a.print(x);
	}
	vector<double> Jacobi(vector<double>& c, vector<vector<double>>& a, int nn)
	{
		vector<vector<double>>B;
		vector<double> C(nn);
		vector<vector<double>>L;
		vector<vector<double>>D;
		vector<vector<double>>R;
		for (int i = 0; i < nn; i++)
		{
			vector<double> l(nn);
			vector<double> d(nn);
			vector<double> r(nn);
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
		B = -InverseMatrix(D) * (L + R);
		C = InverseMatrix(D) * c;
		vector<double> x(nn);
		vector<double> xk(nn);
		do {
			xk = x;
			x = B * xk + C;
		} while (Norm(x, xk) > 1e-3);
		return x;
	}

	void Zeidel(Matrix& a)
	{
		cout << "\nZeidel: ";
		vector<vector<double>>B;
		vector<double> c(n);
		vector<vector<double>>L;
		vector<vector<double>>D;
		vector<vector<double>>R;
		for (int i = 0; i < n; i++)
		{
			vector<double> l(n);
			vector<double> d(n);
			vector<double> r(n);
			for (int j = 0; j < n; j++)
			{
				if (j < i) l[j] = a.getMatrix(i, j);
				if (j == i) d[j] = a.getMatrix(i, j);
				if (j > i) r[j] = a.getMatrix(i, j);
			}
			L.push_back(l);
			D.push_back(d);
			R.push_back(r);
		}
		B = -InverseMatrix(L+D)*R;
		c = InverseMatrix(L+D) * a.getB();
		//B = -InverseMatrix(D) * (L + R);
		//c = InverseMatrix(D) * a.getB();
		vector<double> x(n);
		vector<double> xk(n);
		do {
			/*xk = x;
			for (int i = 0; i < n; i++)
			{
				double s = 0;
				for (int j = 0; j < n; j++)
				{
					if (j >= i)
						s += B[i][j] * xk[j];
					else s += B[i][j] * x[j];
				}
				x[i] = s + c[i];
			}*/
			xk = x;
			x = B * xk + c;
		} while (Norm(x, xk) > 1e-3);
		a.print(x);
	}

	void Complex(Matrix& a, Matrix& b)
	{
		int k = 3;
		vector<vector<double>> C;
		for (int i = 0; i < 2*k; i++)
		{
			vector<double>v(2 * k);
			for (int j = 0; j < 2*k; j++)
			{
				if (i < k && j < k) v[j] = a.getMatrix(i, j);
				else if (i < k && j >= k) v[j] = -b.getMatrix(i, j - k);
				else if (i >= k && j < k) v[j] = b.getMatrix(i - k, j);
				else if (i >= k && j >= k) v[j] = a.getMatrix(i - k, j - k);
 			}
			C.push_back(v);
		}
		a.print(C);
		vector<double> d;
		d = a.getB();
		for (int i = 0; i < k; i++)
			d.push_back(b.getB(i));
		a.print(d);
		cout << endl;
		vector<double> y = Ortogonal(d, C, 2 * k);
		//a.print(y);
		vector<double> x1;
		for (int i = 0; i < k; i++)
			x1.push_back(y[i]);
		vector<double> x2;
		for (int i = k; i < 2 * k; i++)
			x2.push_back(y[i]);
		a.print(x1);
		a.print(x2);

	}
};