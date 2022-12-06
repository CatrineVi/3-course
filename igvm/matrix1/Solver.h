#pragma once
#include "Matrix.h"
#include "VectorB.h"
#include<cmath>

using namespace std;

vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
	vector<double> c(a.size());
	for (int i = 0; i < a.size(); i++)
		c[i] = a[i] + b[i];
	return (c);
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

class Solver : public Matrix, VectorB
{
public:
	Solver(){}
	~Solver(){}
	void Gauss (Matrix& a, VectorB& b)
	{
		vector<double> x(a.getKol_str());
		vector<double> bg = b.getVectorB();
		vector<vector<double>> mg = a.getMatrixM1();
		//double** ag = a.getMatrix();
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
			for (int j = k + 1; j <= a.getKol_stl() - 1; j++) 
				s += mg[k][j] * x[j];
			x[k]=(bg[k] - s) / mg[k][k];
		}
		cout << "\nVector x(G): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}

	double Norm(vector<double> x, vector<double> xk, unsigned n)
	{
		double norm = 0;
		for (int i = 0; i < n; i++)
			norm += pow((x[i] - xk[i]), 2);
		norm = sqrt(norm);
		return norm;
	}

	vector<double> Ax(vector<double>av, vector<unsigned> anc, vector<unsigned>anl,
		vector<double>x)
	{
		vector<double> ax(anl.size()-1);
		for (int i = 0; i < ax.size(); i++)
		{
			double z = 0;
			for (int j = anl[i]; j < anl[i + 1]; j++)
				z += av[j] * x[anc[j]];
			ax[i] = z;
		}
		return ax;
	}

	double ScalarProduct(vector<double>a, vector<double>b)
	{
		double sc = 0;
		for (int i = 0; i < a.size(); i++)
			sc += a[i] * b[i];
		return sc;
	}

	vector<double> kx(double k, vector<double>x)
	{
		vector<double> kx(x.size());
		for (int i = 0; i < x.size(); i++)
			kx[i] = k * x[i];
		return kx;
	}

	void Jacobi(Matrix& a, VectorB& b)
	{
		vector<double> c(a.getKol_str());
		vector<double> bv(a.getKol_Nenul() - a.getKol_str());
		vector<unsigned> bnc(a.getKol_Nenul() - a.getKol_str());
		vector<unsigned> bnl(a.getKol_str()+1);
		vector<double> diagonal(a.getKol_str());
		for (int i = 0; i < a.getKol_str(); i++)
		{
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				if (i == a.getANC(j))
					diagonal[i]=a.getAV(j);
		}
		for (int i = 0, k=0; i < a.getKol_str(); i++)
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
		do{
			x = xk;
			xk = Ax(bv, bnc, bnl, x);
			xk += c;
			iter++;
		} while (Norm(x, xk, a.getKol_str()) > 1e-8);

		cout << "\ndiagonal: ";
		for (int i = 0; i < diagonal.size(); i++)
			cout << setw(3) << diagonal[i];
		cout << "\nBV: ";
		for (int i = 0; i < bv.size(); i++)
			cout << setw(10) << bv[i]; 
		cout << "\nBNC: ";
		for (int i = 0; i < bnc.size(); i++)
			cout << setw(3) << bnc[i];
		cout << "\nBNL: ";
		for (int i = 0; i < bnl.size(); i++)
			cout << setw(3) << bnl[i];
		cout << "\nVector c: ";
		for (int i = 0; i < c.size(); i++)
			cout << setw(10) << c[i];
		cout << "\nVector x(J): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(10) << x[i];
	}

};
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
		} while (Norm(x, xk, a.getKol_str()) > 1e-8);
		cout << "\nVector x(Z): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}

	void fastestDescent(Matrix& a, VectorB& b)
	{
		vector<double> x(a.getKol_str());
		vector<double> xk(a.getKol_str());
		vector<double> r(a.getKol_str());
		do {
			x = xk;
			r = b.getVectorB();
			r = r - Ax(a.getAV(), a.getANC(), a.getANL(), x);
			double k = ScalarProduct(r, r)/
				ScalarProduct(Ax(a.getAV(), a.getANC(), a.getANL(), r),r);
			xk = x + kx(k, r);
		} while (Norm(r, xk, a.getKol_str()) > 1e-8);

		cout << "\nVector x(TFD): ";
		for (int i = 0; i < a.getKol_str(); i++)
			cout << setw(3) << x[i];
	}
};