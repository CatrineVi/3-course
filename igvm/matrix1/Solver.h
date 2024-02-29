#pragma once
#include "Matrix.h"
#include "VectorB.h"
#include <cmath>
#include <ctime>

using namespace std;

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
	vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] + b[i];
	return (c);
}
Matrix operator+(Matrix& a, Matrix& b)
{
	int n = a.getKol_str();
	vector<vector<pair<double, unsigned>>> V;
	for (int k = 0; k < n; k++)
	{
		vector<pair<double, unsigned>> v;
		double s = 0; int t = a.getANL(k);
		for (int i = a.getANL(k), j = b.getANL(k); i < a.getANL(k + 1) && j < b.getANL(k + 1);
			i = (a.getANC(i) <= b.getANC(j) ? i + 1 : i), j = (b.getANC(j) <= a.getANC(t) ? j + 1 : j))
		{
			if (a.getANC(i) == b.getANC(j))
			{
				s = a.getAV(i) + b.getAV(j);
				v.push_back(pair<double, unsigned>(s, a.getANC(i)));
			}
			else if (a.getANC(i) < b.getANC(j))
			{
				s = a.getAV(i);
				v.push_back(pair<double, unsigned>(s, a.getANC(i)));
			}
			else if (a.getANC(i) > b.getANC(j))
			{
				s = b.getAV(j);
				v.push_back(pair<double, unsigned>(s, b.getANC(j)));
			}
			t = i;
		}
		V.push_back(v);
	}
	cerr << "last el:" << V[n - 1][V[n - 1].size() - 1].first << endl;;
	vector<double> v;
	vector<unsigned> nc;
	vector<unsigned> nl;
	unsigned k = 0;
	for (int i = 0; i < n; i++)
	{
		nl.push_back(k);
		for (int j = 0; j < V[i].size(); j++, k++)
		{
			v.push_back(V[i][j].first);
			nc.push_back(V[i][j].second);
		}
	}
	
	nl.push_back(k);
	Matrix c(k, n, v, nc, nl);
	return c;
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
	return (c);
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
vector<double> operator*(Matrix& a, vector<double> x)
{
	vector<double> ax(a.getKol_str());
	for (int i = 0; i < ax.size(); i++)
	{
		double z = 0;
		for (int j = a.getANL(i); j < a.getANL(i+1); j++)
			z += a.getAV(j) * x[a.getANC(j)];
		ax[i] = z;
	}
	return ax;
}
vector<double> operator*(vector<double> x, Matrix& a)
{
	unsigned str = a.getKol_str();
	vector<double> ax(str);
	for (int i = 0; i < ax.size(); i++)
	{
		for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
			ax[a.getANC(j)] += a.getAV(j) * x[a.getANC(j)];
	}
	return ax;
}
Matrix operator*(Matrix& a, Matrix& b)
{
	int n = a.getKol_str();
	vector<vector<pair<double, unsigned>>> V;
	for (int k = 0; k < n; k++)
	{
		vector<pair<double, unsigned>> v;
		for (int j = 0; j < n; j++)
		{
			double s = 0;
			for (int i = a.getANL(k); i < a.getANL(k + 1); i++)
			{
				int ii = a.getANC(i);
				for (int l = b.getANL(ii); l < b.getANL(ii + 1); l++)
				{
					if (b.getANC(l) == j)
					{
						s += a.getAV(i) * b.getAV(l);
						break;
					}
				}
			}
			v.push_back(pair<double, unsigned>(s, j));
		}
		V.push_back(v);
	}
	vector<double> v;
	vector<unsigned> nc;
	vector<unsigned> nl;
	unsigned k = 0;
	for (int i = 0; i < n; i++)
	{
		nl.push_back(k);
		for (int j = 0; j < V[i].size(); j++, k++)
		{
			v.push_back(V[i][j].first);
			nc.push_back(V[i][j].second);
		}
	}
	nl.push_back(k);
	Matrix c(k, n, v, nc, nl);
	return c;
}
vector<pair<double, unsigned>> operator*(vector<pair<double, unsigned>> t, vector<double> w)
{
	vector<pair<double, unsigned>> v;
	for (int k = 0; k < w.size(); k++)
	{
		for (int i = 0; i < t.size(); i++)
		{
			if (t[i].second == k)
			{
				pair<double, unsigned> p(t[i].first * w[k], t[i].second);
				v.push_back(p);
			}
		}
	}
	/*cout << endl << "tw ";
	for (int i = 0; i < v.size(); i++)
	{
		cout << setw(5) << v[i].first<<"("<<v[i].second<<")";
	}*/
	return v;
}

class Solver : public Matrix, VectorB
{
public:
	Solver(){}
	~Solver(){}

	double ScalarProduct(vector<double>a, vector<double>b)
	{
		double sc = 0;
		for (int i = 0; i < a.size(); i++)
			sc += a[i] * b[i];
		return sc;
	}
	double Norm(vector<double> x, vector<double> xk, unsigned n)
	{
		double norm = 0;
		for (int i = 0; i < n; i++)
			norm += pow((x[i] - xk[i]), 2);
		norm = sqrt(norm);
		return norm;
	}
	double Norm(vector<double> x, unsigned n)
	{
		double norm = 0;
		for (int i = 0; i < n; i++)
			norm += pow(x[i], 2);
		norm = sqrt(norm);
		return norm;
	}
	Matrix InverseL(Matrix& l)
	{
		vector<vector<double>> e;

		for (int i = 0; i < l.getKol_str(); i++)
		{
			vector<double> v(l.getKol_str());
			for (int j = 0; j < l.getKol_str(); j++)
			{
				if (i == j)
					v[j] = 1;
				else v[j] = 0;
			}
			e.push_back(v);
		}
		Matrix m = l;
		double t;
		for (int k = 1; k < l.getKol_str(); k++)
		{
			for (int i = l.getANL(k); i < l.getANL(k+1) - 1; i++)
			{
				int jj = l.getANC(i);
				t = l.getAV(i);
				for (int j = 0; j < l.getKol_str(); j++)
					e[k][j] -= e[jj][j] * t;
			}
		}
		return CreateM(e);
	}
	Matrix InverseU(Matrix& u)
	{
		vector<vector<double>> e;

		for (int i = 0; i < u.getKol_str(); i++)
		{
			vector<double> v(u.getKol_str());
			for (int j = 0; j < u.getKol_str(); j++)
			{
				if (i == j)
					v[j] = 1;
				else v[j] = 0;
			}
			e.push_back(v);
		}
		Matrix m = u;
		double t;
		for (int k = 0; k < u.getKol_str(); k++)
		{
			t = u.getAV(u.getANL(k));
			for (int j = 0; j < u.getKol_str(); j++)
				e[k][j] /= t;
			for (int j = u.getANL(k); j < u.getANL(k + 1); j++)
				m.setAV(j, u.getAV(j) / t);
		}
		for (int k = u.getKol_str() - 2; k >= 0; k--)
		{
			for (int i = u.getANL(k+1)-1; i > u.getANL(k); i--)
			{
				int jj = u.getANC(i);
				t = m.getAV(i);
				for (int j = 0; j < u.getKol_str(); j++)
				{
					e[k][j] -= e[jj][j] * t;
				}
			}
		}
		return CreateM(e);
	}
	vector<vector<double>> Inverse(Matrix& a, vector<vector<double>> b)
	{
		vector<vector<double>> e;
		for (int i = 0; i < a.getKol_str(); i++)
		{
			vector<double> v(a.getKol_str());
			v[i] = 1;
			e.push_back(v);
		}
		vector<vector<double>> matrix = b;
		double t;
		for (int k = 0; k < a.getKol_str(); k++)
		{
			t = matrix[k][k];
			for (int j = 0; j < a.getKol_str(); j++)
			{
				matrix[k][j] /= t;
				e[k][j] /= t;
			}
			for (int i = k + 1; i < a.getKol_str(); i++)
			{
				t = matrix[i][k];
				for (int j = 0; j < a.getKol_str(); j++)
				{
					matrix[i][j] -= matrix[k][j] * t;
					e[i][j] -= e[k][j] * t;
				}
			}
		}
		for (int k = a.getKol_str() - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				t = matrix[i][k];

				for (int j = 0; j < a.getKol_str(); j++)
				{
					matrix[i][j] -= matrix[k][j] * t;
					e[i][j] -= e[k][j] * t;
				}
			}
		}
		return e;
	}

	Matrix CreateM(vector<vector<double>> m)
	{
		vector<double> av;
		vector<unsigned> anc;
		vector<unsigned> anl;
		int kn = 0;
		for (int i = 0; i < m.size(); i++)
		{
			bool t = true;
			for (int j = 0; j < m[i].size(); j++)
			{
				if (m[i][j] != 0)
				{
					if (t == true)
					{
						anl.push_back(kn);
						t = false;
					}
					av.push_back(m[i][j]);
					anc.push_back(j);
					kn++;
				}
			}
			t = true;
		}
		anl.push_back(kn);
		Matrix M(kn, m.size(), av, anc, anl);
		return M;
	}

	void productAB(Matrix& a, Matrix& b)
	{
		int n = a.getKol_str();
		vector<vector<pair<double, unsigned>>> V;
		for (int k = 0; k < n; k++)
		{
			vector<pair<double, unsigned>> v;
			for (int j = 0; j < n; j++)
			{
				double s = 0;
				for (int i = a.getANL(k); i < a.getANL(k + 1); i++)
				{
					int ii = a.getANC(i);
					for (int l = b.getANL(ii); l < b.getANL(ii+1); l++)
					{
						if (b.getANC(l) == j)
						{
							s += a.getAV(i) * b.getAV(l);
							break;
						}
					}
				}
				v.push_back(pair<double, unsigned> (s,j));
			}
			V.push_back(v);
		}
	}

	vector<vector<double>> productAB(vector<vector<double>> a, vector<vector<double>> b)
	{
		vector<vector<double>> ab;
		for (int i = 0; i < a.size(); i++)
		{
			vector<double> v(a.size());
			for (int l = 0; l < a.size(); l++)
			{
				double s = 0;
				for (int j = 0; j < a.size(); j++)
				{
					s += a[i][j] * b[j][l];
				}
				v[l] = s;
			}
			ab.push_back(v);
		}
		return ab;
	}

	vector<double> axpy(double a, vector<double> x, double p, vector<double> y)
	{
		return a * x + p * y;
	}
	
	vector<pair<vector<vector<double>>,vector<vector<double>>>> LU(Matrix& a, vector<vector<double>> l, vector<vector<double>> u)
	{
		for (int k = 0; k < a.getKol_str(); k++)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				if (a.getMatrixM1(k, j) != 0)
				{
					double lu = 0;
					for (int i = 0; i < j - 1; i++)
						lu += l[k][i] * u[i][j];
					l[k][j] = 1 / u[j][j] * (a.getMatrixM1(k, j) - lu);
				}
				else l[k][j] = 0;
			}
			l[k][k] = 1;
			for (int j = k; j < a.getKol_str(); j++)
			{
				if (a.getMatrixM1(k, j) != 0)
				{
					double lu = 0;
					for (int i = 0; i <= k - 1; i++)
						lu += l[k][i] * u[i][j];
					u[k][j] = a.getMatrixM1(k, j) - lu;
				}
				else u[k][j] = 0;
			}
		}
		vector<pair<vector<vector<double>>, vector<vector<double>>>>lu(1);
		lu[0].first = l; lu[0].second = u;
		return lu;
	}
	vector<pair<Matrix, Matrix>>LU(Matrix& a)
	{
		vector<pair<Matrix, Matrix>>lu(1);
		Matrix L((a.getKol_Nenul() - a.getKol_str()) / 2 + a.getKol_str(), a.getKol_str());
		Matrix U((a.getKol_Nenul() - a.getKol_str()) / 2 + a.getKol_str(), a.getKol_str());
		L.setANL(0, 0);
		U.setANL(0, 0);
		for (int i = 0, k = 0, n = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
			{
				if (i >= a.getANC(j)) {
					L.setANC(k++, a.getANC(j));
				}
				if (i <= a.getANC(j)) {
					U.setANC(n++, a.getANC(j));
				}
			}
			L.setANL(i+1, k);
			U.setANL(i+1, n);
		}

		for (int k = 0; k < a.getKol_str(); k++)
		{
			int m = 0;
			for (int j = L.getANL(k); j < L.getANL(k+1); j++, m++)
			{
				double sum = 0;
				for (int i = L.getANL(k); i < j; i++)
				{
					unsigned ii = L.getANC(i);
					for (int l = U.getANL(ii); l < U.getANL(ii + 1); l++)
					{
						if (U.getANC(l) == L.getANC(j) && L.getANC(l)<L.getANC(j))
						{
							sum += L.getAV(i) * U.getAV(l);
							break;
						}
					}
				}
				L.setAV(j, 1 / U.getAV(U.getANL(L.getANC(j))) * (a.getAV(a.getANL(k) + m) - sum));
			}
			L.setAV(L.getANL(k + 1) - 1, 1);
			m--;
			for (int j = U.getANL(k); j < U.getANL(k + 1); j++,m++)
			{
				double sum = 0;
				for (int i = L.getANL(k); i < L.getANL(k + 1)-1; i++)
				{
					unsigned ii = L.getANC(i);
					for (int l = U.getANL(ii); l < U.getANL(ii + 1); l++)
					{
						if (U.getANC(l) == U.getANC(j))
						{
							sum += L.getAV(i) * U.getAV(l);
							break;
						}
					}
				}
				U.setAV(j, a.getAV(a.getANL(k) + m) - sum);
			}
		}

		/*for (int k = 0; k < a.getKol_str(); k++)
		{
			for (int j = 0; j <= k - 1; j++)
			{
				if (a.getMatrixM1(k, j) != 0)
				{
					double lu = 0;
					for (int i = 0; i < j - 1; i++)
						lu += l[k][i] * u[i][j];
					l[k][j] = 1 / u[j][j] * (a.getMatrixM1(k, j) - lu);
				}
				else l[k][j] = 0;
			}
			l[k][k] = 1;
			for (int j = k; j < a.getKol_str(); j++)
			{
				if (a.getMatrixM1(k, j) != 0)
				{
					double lu = 0;
					for (int i = 0; i <= k - 1; i++)
						lu += l[k][i] * u[i][j];
					u[k][j] = a.getMatrixM1(k, j) - lu;
				}
				else u[k][j] = 0;
			}
		}*/

		lu[0].first = L; lu[0].second = U;
		return lu;
	}

	void Gauss (Matrix& a, VectorB& b)
	{
		vector<double> x(a.getKol_str());
		vector<double> bg = b.getVectorB();
		vector<vector<double>> mg = a.getMatrixM1();
		//double** ag = a.getMatrix();
		unsigned int start = clock();
		int iter = 0;
		for (int k = 0; k < a.getKol_str(); k++)
		{
			for (int i = k + 1; i < a.getKol_str(); i++)
			{
				double t = mg[i][k] / mg[k][k];
				bg[i] -= t * bg[k];
				for (int j = k; j < a.getKol_stl(); j++) 
					mg[i][j] -= t * mg[k][j];
			}
		}
		x[a.getKol_str()-1] = bg[a.getKol_str() - 1] / mg[a.getKol_stl() - 1][a.getKol_str() - 1];
		
		for (int k = a.getKol_str() - 2; k >= 0; k--)
		{
			double s = 0;
			for (int j = k + 1; j <= a.getKol_stl() - 1; j++,iter++)
				s += mg[k][j] * x[j];
			x[k]=(bg[k] - s) / mg[k][k];
		}
		unsigned int end = clock();
		unsigned int time = end - start;
		cout << "\nVector x(G): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << " " << x[i];
		cout << "\ntime(G): " << time;
		cout << "\niterations(G): " << iter;
	}

	void Jacobi(Matrix& a, VectorB& b)
	{
		vector<double> c(a.getKol_str());
		Matrix B(a.getKol_Nenul() - a.getKol_str(), a.getKol_str());
		vector<double> diagonal(a.getKol_str());
		for (int i = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i == a.getANC(j))
					diagonal[i]=a.getAV(j);
		}

		for (int i = 0, k = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i != a.getANC(j)) {
					B.setAV(k, -a.getAV(j) / diagonal[i]);
					B.setANC(k++, a.getANC(j));
				}
			B.setANL(i, a.getANL(i) - i);
			c[i] = b.getVectorB(i) / diagonal[i];
		}
		vector<double> x(a.getKol_str());
		vector<double> xk(a.getKol_str());
		int iter = 0;
		unsigned int start = clock();
		do{
			x = xk;
			xk = B * x + c;
			iter++;
		} while (Norm(x, xk, a.getKol_str()) > 1e-8);
		unsigned int end = clock();
		unsigned int time = end - start;

		cout << "\nVector x(J): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
		cout << "\ntime(J): " << time;
		cout << "\niterations(J): " << iter;
	}

	void Zeidel(Matrix& a, VectorB& b)
	{
		vector<double> c(a.getKol_str());
		vector<double> bv(a.getKol_Nenul() - a.getKol_str());
		vector<unsigned> bnc(a.getKol_Nenul() - a.getKol_str());
		vector<unsigned> bnl(a.getKol_str() + 1);
		vector<double> diagonal(a.getKol_str());
		for (int i = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i == a.getANC(j))
					diagonal[i] = a.getAV(j);
		}
		for (int i = 0, k = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i != a.getANC(j)) {
					bv[k] = -a.getAV(j) / diagonal[i];
					bnc[k++] = a.getANC(j);
				}
			bnl[i] = a.getANL(i) - i;
			c[i] = b.getVectorB(i) / diagonal[i];
		}
		bnl[a.getKol_str()] = bv.size();
		vector<double> x(a.getKol_str());
		vector<double> xk(a.getKol_str());
		int iter = 0;
		unsigned int start = clock();
		do {
			x = xk;
			for (int i = 0; i < a.getKol_str(); i++)
			{
				double z = 0;
				for (int j = bnl[i]; j < bnl[i + 1]; j++)
				{
					if (bnc[j] < i)
						z += bv[j] * xk[bnc[j]];
					else if (bnc[j] > i)
						z += bv[j] * x[bnc[j]];
				}
				z += c[i];
				xk[i] = z;
 			}
			iter++;
		} while (Norm(x, xk, a.getKol_str()) > 1e-8);
		unsigned int end = clock();
		unsigned int time = end - start;
		cout << "\nVector x(Z): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
		cout << "\ntime(Z): " << time;
		cout << "\niterations(Z): " << iter;
	}

	void fastestDescent(Matrix& a, VectorB& b)
	{
		vector<double> x(a.getKol_str());
		vector<double> xk(a.getKol_str());
		vector<double> r(a.getKol_str());
		int iter = 0;
		unsigned int start = clock();
		do {
			x = xk;
			r = b.getVectorB();
			r = r - a * x;
			double k = ScalarProduct(r, r) /
				ScalarProduct(a * r, r);
			xk = x + k * r;
			iter++;
		} while (Norm(r, xk, a.getKol_str()) > 1e-8);
		unsigned int end = clock();
		unsigned int time = end - start;

		cout << "\nVector x(TFD): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
		cout << "\ntime(tfd): " << time;
		cout << "\niterations(tfd): " << iter;
	}

	void ortoArnald(Matrix& a, int m, vector<double>& v)
	{
		vector<vector<double>> basis;
		basis.push_back(v);
		for (int j = 0; j < m; j++)
		{
			vector<double> w = a * v;
			for (int i = 0; i <= j; i++)
			{
				double h = ScalarProduct(w, v);
				w = w - h * v;
			}
			double h = Norm(w, a.getKol_str());
			if (h == 0) break;
			v = w / h;
			basis.push_back(v);
		}
		cout << "\nBasis: " << endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < a.getKol_str(); j++)
				cout << setw(10) << basis[i][j];
			cout << endl;
		}
	}

	void FOM(Matrix& a, VectorB& b,int m)
	{
		vector<double> x(a.getKol_str());
		vector<double> r;
		double beta;
		vector<vector<double>> v(m);
		vector<double>e(m); e[0] = 1;
		vector<double> f;
		vector<double>Ax0;
		vector<vector<double>> h;
		for (int i = 0; i < m; i++) {
			vector<double> c;
			for (int j = 0; j < m; j++)
				c.push_back(0);
			h.push_back(c);
		}
		do {
			r = b.getVectorB() - a * x;
			beta = Norm(r, a.getKol_str());
			f = beta * e;
			v[0] = (r / beta);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
					h[i][j] = 0;

			for (int j = 0; j < m; j++)
			{
				vector<double> w = a * v[j];
				for (int i = 0; i <= j; i++)
				{
					h[i][j] = ScalarProduct(w, v[i]);
					w = w - h[i][j] * v[i];
				}
				if (j+1 < m)
				{
					h[j + 1][j] = Norm(w, a.getKol_str());
					if (h[j + 1][j] == 0) { m = j; break; }
					v[j+1]=(w / h[j + 1][j]);
				}
				else break;
			}
			for (int k = 0; k < m; k++)
			{
				for (int i = k + 1; i < m; i++)
				{
					double t = h[i][k] / h[k][k];
					f[i] -= t * f[k];
					for (int j = k; j < m; j++)
						h[i][j] -= t * h[k][j];
				}
			}
			vector<double>y(m);
			y[m - 1] = f[m - 1] / h[m - 1][m - 1];
			for (int k = m - 2; k >= 0; k--)
			{
				double s = 0;
				for (int j = k + 1; j <= m - 1; j++)
					s += h[k][j] * y[j];
				y[k] = (f[k] - s) / h[k][k];
			}
			vector<double>x0(a.getKol_str());
		
			x0 = x;
			
			vector<double>yv(a.getKol_str());

			for (int i = 0;i < m; i++)
			{
				yv = yv + y[i] * v[i];
			}
			x = x0 + yv;
			Ax0 = a * x;
		} while (Norm(b.getVectorB(), Ax0, a.getKol_str()) > 1e-8);
		cout << "\nVector x(FOM): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}

	vector<double> CG(Matrix& a, VectorB& b)
	{
		vector<double> x(a.getKol_str());
		vector<double> r = b.getVectorB() - a * x;
		vector<double> r1;
		vector<double> p = r;
		vector<double> p1;
		vector<double> Ap;
		for (int j = 0; ; j++)
		{
			Ap = a * p;
			double sr = ScalarProduct(r, r);
			double alfa = sr / ScalarProduct(Ap, p);
			x = x + alfa * p;
			r1 = r - alfa * Ap;
			double beta = ScalarProduct(r1, r1) / sr;
			if (Norm(r1, a.getKol_str()) < 1e-8)
				break;
			p1 = r1 + beta * p;
			r = r1; p = p1;
		}
		//cout << "\nVector x(CG): ";
		//for (int i = 0; i < a.getKol_str(); i++)
			//cout << setw(3) << x[i] << "; ";
		return x;
	}

	void GMRES(Matrix& a, VectorB& b, int m)
	{
		vector<double> x(a.getKol_str());
		vector<double> r = b.getVectorB() - a * x;
		double beta = Norm(r, a.getKol_str());
		int p = m;
		vector<vector<double>> v(m+1);
		vector<double>e(m+1); e[0] = 1;
		vector<pair<double, double>> G(m);
		vector<vector<double>> h;
		for (int i = 0; i < m + 1; i++) {
			vector<double> c;
			for (int j = 0; j < m; j++)
				c.push_back(0);
			h.push_back(c);
		}
		vector<double> g(m + 1);
		do {
			for (int i = 0; i < m + 1; i++)
				for (int j = 0; j < m; j++)
					h[i][j] = 0;
			g = beta * e;
			v[0] = (r / beta);
			for (int i = 0; i < m; i++)
			{
				vector<double> w = a * v[i];
				for (int k = 0; k <= i; k++)
				{
					h[k][i] = ScalarProduct(w, v[k]);
					w = w - h[k][i] * v[k];
				}
				h[i + 1][i] = Norm(w, a.getKol_str());
				v[i + 1] = (w / h[i + 1][i]);
				for (int k = 0; k < i; k++)
				{
					double hki = h[k][i];
					h[k][i] = G[k].first * hki - G[k].second * h[k + 1][i];
					h[k + 1][i] = G[k].second * hki + G[k].first * h[k + 1][i];
				}
				G[i].first = h[i][i] / (sqrt(h[i][i] * h[i][i] + h[i + 1][i] * h[i + 1][i]));
				G[i].second = -h[i + 1][i] / (sqrt(h[i][i] * h[i][i] + h[i + 1][i] * h[i + 1][i]));
				double hii = h[i][i];
				h[i][i] = G[i].first * hii - G[i].second * h[i + 1][i];
				h[i + 1][i] = G[i].second * hii + G[i].first * h[i + 1][i];;
				double gi = g[i];
				g[i] = G[i].first * g[i] - G[i].second * g[i + 1];
				g[i + 1] = G[i].second * gi + G[i].first * g[i + 1];
				/*if (abs(g[i + 1]) < 1e-8)
				{
					p = i; break;
				}*/
			}
			vector<double>y(m);
			y[m - 1] = g[m - 1] / h[m - 1][m - 1];
			for (int k = m - 2; k >= 0; k--)
			{
				double s = 0;
				for (int j = k + 1; j <= m - 1; j++)
					s += h[k][j] * y[j];
				y[k] = (g[k] - s) / h[k][k];
			}

			vector<double>x0(a.getKol_str());
			x0 = x;
			vector<double>yv(a.getKol_str());
			for (int i = 0; i < p; i++)
			{
				yv = yv + y[i] * v[i];
			}
			x = x0 + yv;

			if (p < m) break;
			r = b.getVectorB() - a * x;
			beta = Norm(r, a.getKol_str());

		} while(beta > 1e-8);
		/*cout << endl;
		for (int i = 0; i < m + 1; i++) {
			for (int j = 0; j < m; j++)
				cout << setw(8) << h[i][j];
			cout << endl;
		}*/

		cout << "\nVector x(GMRES): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}

	void P_FOM(Matrix& a, VectorB& b, int m)
	{
		Matrix L = LU(a)[0].first;
		Matrix U = LU(a)[0].second;
		Matrix L1 = InverseL(L);
		Matrix U1 = InverseU(U);
		vector<vector<double>> l;
		vector<vector<double>> u;
		for (int i = 0; i < a.getKol_str(); i++)
		{
			vector<double> v(a.getKol_str());
			l.push_back(v);
			u.push_back(v);
		}
		l = LU(a, l, u)[0].first;
		u = LU(a, l, u)[0].second;
		//L.print();
		//cout << endl;
		//a.print(l);
		//InverseL(L).print();
		//cout << endl;
		//a.print(Inverse(a, l));
		//U.print();
		//cout << endl;
		//a.print(u);
		//InverseU(U).print();
		//cout << endl;
		//a.print(Inverse(a,u));

		vector<double> x(a.getKol_str());
		vector<double> r;
		double beta;
		vector<vector<double>> v(m);
		vector<double>e(m); e[0] = 1;
		vector<double> f;
		vector<double>Ax0;
		vector<vector<double>> h;
		for (int i = 0; i < m; i++) {
			vector<double> c;
			for (int j = 0; j < m; j++)
				c.push_back(0);
			h.push_back(c);
		}
		do {
			r = U1 * (L1 *(b.getVectorB() - a * x));
			beta = Norm(r, a.getKol_str());
			f = beta * e;
			v[0] = (r / beta);
			for (int i = 0; i < m; i++)
				for (int j = 0; j < m; j++)
					h[i][j] = 0;

			for (int j = 0; j < m; j++)
			{
				vector<double> w = U1 * (L1 * (a * v[j]));
				for (int i = 0; i <= j; i++)
				{
					h[i][j] = ScalarProduct(w, v[i]);
					w = w - h[i][j] * v[i];
				}
				if (j + 1 < m)
				{
					h[j + 1][j] = Norm(w, a.getKol_str());
					if (h[j + 1][j] == 0) { m = j; break; }
					v[j + 1] = (w / h[j + 1][j]);
				}
				else break;
			}
			for (int k = 0; k < m; k++)
			{
				for (int i = k + 1; i < m; i++)
				{
					double t = h[i][k] / h[k][k];
					f[i] -= t * f[k];
					for (int j = k; j < m; j++)
						h[i][j] -= t * h[k][j];
				}
			}
			vector<double>y(m);
			y[m - 1] = f[m - 1] / h[m - 1][m - 1];
			for (int k = m - 2; k >= 0; k--)
			{
				double s = 0;
				for (int j = k + 1; j <= m - 1; j++)
					s += h[k][j] * y[j];
				y[k] = (f[k] - s) / h[k][k];
			}
			vector<double>x0(a.getKol_str());

			x0 = x;

			vector<double>yv(a.getKol_str());

			for (int i = 0; i < m; i++)
			{
				yv = yv + y[i] * v[i];
			}
			x = x0 + yv;
			Ax0 = a * x;
		} while (Norm(b.getVectorB(), Ax0, a.getKol_str()) > 1e-8);
		cout << "\nVector x(P_FOM): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
		
	}

	void P_CG(Matrix& a, VectorB& b)
	{
		Matrix L = LU(a)[0].first;
		Matrix U = LU(a)[0].second;
		Matrix L1 = InverseL(L);
		Matrix U1 = InverseU(U);

		vector<double> x(a.getKol_str());
		vector<double> r = b.getVectorB() - a * x;
		vector<double> r1;
		vector<double> z = U1 * (L1 * r);
		vector<double> z1;
		vector<double> p = r;
		vector<double> p1;
		vector<double> Ap;
		for (int j = 0; ; j++)
		{
			Ap = a * p;
			double sr = ScalarProduct(z, r);
			double alfa = sr / ScalarProduct(Ap, p);
			x = x + alfa * p;
			r1 = r - alfa * Ap;
			z1 = U1 * (L1 * r1);
			double beta = ScalarProduct(z1, r1) / sr;
			if (Norm(r1, a.getKol_str()) < 1e-8)
				break;
			p1 = z1 + beta * p;
			r = r1; p = p1; z = z1;
		}
		cout << "\nVector x(P_CG): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}

	void AISM_FOM(Matrix& a, VectorB& b, int m)
	{
		int n = a.getKol_str();
		vector<double> W(n);
		double bt = 0.5;
		for (int i = 0; i < n; i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i == a.getANC(j))
					W[i] = bt * a.getAV(j);
		}
		vector<double> W1(n);
		for (int i = 0; i < n; i++)
			W1[i] = 1.0 / W[i];
		a.print(W1);

		vector<double> D(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i == a.getANC(j))
					D[i] = a.getAV(j);
		}

		Matrix Z(a.getKol_Nenul(), n);
		for (int l = 0; l < n; l++)
		{
			for (int i = 0, k = 0; i < n; i++)
			{
				for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
					if (i == a.getANC(j)) {
						Z.setAV(k, W[i] - a.getAV(j));
						Z.setANC(k++, a.getANC(j));
					}
					else
					{
						Z.setAV(k, - a.getAV(j));
						Z.setANC(k++, a.getANC(j));
					}
				Z.setANL(i, a.getANL(i));
			}
		}
		Z.print();
		Matrix ZT(Z.getKol_Nenul(), n);
		for (int l = 0, k = 0; l < n; l++)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = Z.getANL(i); j < Z.getANL(i + 1); j++)
					if (l == Z.getANC(j)) {
						ZT.setAV(k, Z.getAV(j));
						ZT.setANC(k++, Z.getANC(k-1));
					}
				ZT.setANL(i, Z.getANL(i));
			}
		}
		//ZT.print();


		vector<pair<double, unsigned>> U(n);
		for (int k = 0; k < n; k++)
		{
			U[k].first = 1;
			U[k].second = k;
		}
		vector<vector<pair<double, unsigned>>> V;
		for (int k = 0; k < n; k++)
		{
			vector<pair<double, unsigned>> v;
			for (int i = ZT.getANL(k); i < ZT.getANL(k + 1); i++)
			{
				pair<double, unsigned> p(ZT.getAV(i), ZT.getANC(i));
				v.push_back(p);
			}
			V.push_back(v);
		}
	
		
		vector<pair<double, unsigned>> S(n);
		vector<vector<pair<double, unsigned>>> T(n);
		double delta = 0;
		for (int k = 0; k < n; k++)
		{
			S[k] = U[k]; T[k] = V[k];
			for (int i = 0; i < k; i++)
			{
				std::cout << std::endl << k << ":" << i ;
				vector<pair<double, unsigned>> tw = T[i] * W1;
				for (int l = 0; l < tw.size(); l++)
				{
					if (tw[l].second == U[k].second)
					{
						delta = tw[l].first * U[k].first;
						cout << endl << "delta " << delta << endl;
					}
				}
				if (abs(delta / D[i]) > 0.0001)
				{

				}
			}
		}

	}
};