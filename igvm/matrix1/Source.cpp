#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Matrix
{
	double** m;
	unsigned kol_nenull, kol_str, kol_stl;
public:
	Matrix() :kol_nenull(0), kol_str(0), kol_stl(0), m(NULL) {}
	~Matrix()
	{
		kol_nenull = 0; kol_str = 0; kol_stl = 0; m = NULL;
	}
	void read()
	{
		ifstream fin("Test_int.mtx");
		if (!fin)
			cout << "Not found file" << endl;
		else
		{
			string s;
			getline(fin, s);

			fin >> kol_str >> kol_stl >> kol_nenull;

			m = new double* [kol_str];
			for (int i = 0; i < kol_str; i++)
				m[i] = new double[kol_stl];

			for (int i = 0; i < kol_str; i++)
				for (int j = 0; j < kol_stl; j++)
					m[i][j] = 0;

			unsigned str = 0, stl = 0;
			double znach = 0;
			for (int i = 0; i < kol_nenull; i++)
			{
				fin >> str >> stl >> znach;
				m[str - 1][stl - 1] = znach;
			}
		}
		fin.close();
	}

	void print()
	{
		for (int i = 0; i < kol_str; i++)
		{
			for (int j = 0; j < kol_stl; j++)
				cout << setw(3) << m[i][j];
			cout << endl;
		}

	}
};

int main()
{
	Matrix m;
	m.read();
	m.print();
	return 0;
}