#pragma once
#include "Matrix.h";
#include <iostream>

using namespace std;

class VectorB:public Matrix
{
	vector<double> b;
public:
	VectorB() {}
	~VectorB() {}
	void calculationVectorB(Matrix& a)
	{
		b.resize(a.getKol_str());
		for (int i = 0; i < a.getKol_str(); i++)
		{
			double z = 0;
			for (int j = a.getANL(i); j < a.getANL(i + 1); j++)
				z += a.getAV(j);
			b[i] = z;
		}
	}

	double getVectorB(unsigned i) { return b[i]; }
	vector<double> getVectorB() { return b; }

	void print()
	{
		cout << "\nVector b: ";
		for (int i = 0; i < b.size(); i++)
			cout << setw(3) << b[i];
	}

};