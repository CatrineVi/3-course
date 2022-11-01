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
		unsigned str0 = a.getANC(0);
		double b0 = 0;
		for (int i = 0; i < a.getKol_Nenul(); i++)
		{
			if (str0 > a.getANC(i))
			{
				b.push_back(b0);
				b0 = 0;
			}
			b0 += a.getAV(i);
			str0 = a.getANC(i);
		}
		b.push_back(b0);
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