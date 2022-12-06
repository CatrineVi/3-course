#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

class Matrix
{
	double** m;
	unsigned kol_nenull, kol_str, kol_stl;
	vector<double> av;
	vector<unsigned> anc;
	vector<unsigned> anl;
	vector < vector < double>> m1;

public:
	Matrix() :kol_nenull(0), kol_str(0), kol_stl(0), m(NULL) {}
	~Matrix()
	{
		kol_nenull = 0; kol_str = 0; kol_stl = 0; m = NULL;
	}
	void read(const string file)
	{
		ifstream fin(file);
		if (!fin)
			cout << "Not found file" << endl;
		else
		{
			string s;
			getline(fin, s);

			fin >> kol_str >> kol_stl >> kol_nenull;

			/*m = new double* [kol_str];
			for (int i = 0; i < kol_str; i++)
				m[i] = new double[kol_stl];

			for (int i = 0; i < kol_str; i++)
				for (int j = 0; j < kol_stl; j++)
					m[i][j] = 0;*/

			for (int i = 0; i < kol_str; i++) {
				vector<double> v;
				for (int j = 0; j < kol_stl; j++)
					v.push_back(0);
				m1.push_back(v);
			}
					
			struct Node
			{
				unsigned str, stl;
				double znach;
				Node(unsigned str, unsigned stl, double znach)
				{
					this->str = str;
					this->stl = stl;
					this->znach = znach;
				}
			};

			vector<Node> temp;
			unsigned str = 0, stl = 0;
			double znach = 0;

			for (int i = 0; i < kol_nenull; i++)
			{
				fin >> str >> stl >> znach;
				//m[str - 1][stl - 1] = znach;

				m1[str - 1][stl - 1] = znach;
				temp.push_back(Node(str - 1, stl - 1, znach));
			}
			
			sort(temp.begin(), temp.end(), [](const Node& a, const Node& b)
				{return tie(a.str, a.stl) < tie(b.str, b.stl); });

			unsigned str0 = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				av.push_back(temp[i].znach);
				anc.push_back(temp[i].stl);

				if (str0 < temp[i].str + 1)
				{
					anl.push_back(i);
					str0 = temp[i].str + 1;
				}
			}
			cout << endl;
			anl.push_back(kol_nenull);
		}
		fin.close();
	}

	double getAV(unsigned i) { return av[i]; }
	vector<double> getAV() { return av; }
	unsigned getANC(unsigned i) { return anc[i]; }
	vector<unsigned> getANC() { return anc; }
	unsigned getANL(unsigned i) { return anl[i]; }
	vector<unsigned> getANL() { return anl; }
	unsigned getKol_Nenul() { return kol_nenull; }
	unsigned getKol_str() { return kol_str; }
	unsigned getKol_stl() { return kol_stl; }
	double getMatrix(unsigned i, unsigned j) { return m[i][j]; }
	double** getMatrix() { return m; }
	vector<vector<double>> getMatrixM1() { return m1; }
	double getMatrixM1(unsigned i, unsigned j) { return m1[i][j]; }

	void print()
	{
		/*for (int i = 0; i < kol_str; i++)
		{
			for (int j = 0; j < kol_stl; j++)
				cout << setw(3) << m[i][j];
			cout << endl;
		}*/
		for (int i = 0; i < kol_str; i++)
		{
			for (int j = 0; j < kol_stl; j++)
				cout << setw(3) << m1[i][j];
			cout << endl;
		}
		cout << "\nav: ";
		for (int i = 0; i < kol_nenull; i++)
			cout << setw(3) << av[i];

		cout << "\nanc: ";
		for (int i = 0; i < kol_nenull; i++)
			cout << setw(3) << anc[i];

		cout << "\nanl: ";
		for (int i = 0; i < kol_str + 1; i++)
			cout << setw(3) << anl[i];
	}
};