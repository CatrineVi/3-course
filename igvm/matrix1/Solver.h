#pragma once
#include "Matrix.h"
#include "VectorB.h"
#include<cmath>

using namespace std;

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

};

