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
	Matrix(unsigned _k_n, unsigned _k_str)
	{
		kol_nenull = _k_n;
		kol_str = _k_str;
		kol_stl = _k_str;
		for (int i = 0; i < _k_n; i++)
		{
			av.push_back(0);
			anc.push_back(0);
		}
		for (int i = 0; i < _k_str; i++)
			anl.push_back(0);
		anl.push_back(_k_n);
	}
	Matrix(unsigned _k_str)
	{
		kol_str = _k_str;
		kol_stl = _k_str;
		for (int i = 0; i < _k_str+1; i++)
			anl.push_back(0);
	}
	Matrix(unsigned _k_n, unsigned _k_str, vector<double> _av, vector<unsigned> _anc, vector<unsigned> _anl)
	{
		kol_nenull = _k_n;
		kol_str = _k_str;
		kol_stl = _k_str;
		av = _av;
		anc = _anc;
		anl = _anl;
	}
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

	bool check(unsigned _str, unsigned _stl)
	{
		for (int i = anl[_str]; i < anl[_str + 1]; i++)
			if (_stl == anc[i])
				return 1;
		return 0;
	}

	void newEl(double _zn, unsigned _str, unsigned _stl)
	{
		if (av.empty())
		{
			kol_nenull++;
			av.push_back(_zn);
			anc.push_back(_stl);
			anl.push_back(0);
			anl.push_back(kol_nenull);
		}
		else if (check(_str, _stl))
		{
			for (int i = anl[_str]; i < anl[_str + 1]; i++)
				if (_stl == anc[i])
					av[i] = _zn;
		}
		else {
			kol_nenull++;
			auto iter1 = av.cbegin();
			auto iter2 = anc.cbegin();
			auto iter3 = anl.cend();
			if (_str > anl.size()-1)
			{
				av.push_back(_zn);
				anc.push_back(_stl);
				anl.insert(iter3-1, kol_nenull - 1);
			}
			else {
				for (int i = anl[_str]; i < anl[_str + 1]; i++)
				{
					if (_stl < anc[i])
					{
						av.insert(iter1 + i, _zn);
						anc.insert(iter2 + i, _stl);
						break;
					}
				}
			}
			for (int i = _str + 1; i < anl.size(); i++)
				anl[i] += 1;
		}
	}

	double getAV(unsigned i) { return av[i]; }
	vector<double> getAV() { return av; }
	void setAV(unsigned i, double zn) { av[i] = zn; }
	void setAV(vector<double> v) { av = v; }

	unsigned getANC(unsigned i) { return anc[i]; }
	vector<unsigned> getANC() { return anc; }
	void setANC(unsigned i, unsigned zn) { anc[i] = zn; }
	void setANC(vector<unsigned> v) { anc = v; }

	unsigned getANL(unsigned i) { return anl[i]; }
	vector<unsigned> getANL() { return anl; }
	void setANL(unsigned i, unsigned zn) { anl[i] = zn; }
	void setANL(vector<unsigned> v) { anc = v; }

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
				cout << setw(3) << m1[i][j];
			cout << endl;
		}*/
		cout << "\nav: ";
		for (int i = 0; i < kol_nenull; i++)
			cout << setw(3) << av[i] <<"; ";

		cout << "\nanc: ";
		for (int i = 0; i < kol_nenull; i++)
			cout << setw(3) << anc[i];

		cout << "\nanl: ";
		for (int i = 0; i < anl.size(); i++)
			cout << setw(3) << anl[i];
	}
	void print(vector<vector<double>> m)
	{
		for (int i = 0; i < kol_str; i++)
		{
			for (int j = 0; j < kol_stl; j++)
				cout << setw(3) << m[i][j];
			cout << endl;
		}
	}
	void print(vector<double> v)
	{
		for (int i = 0; i < v.size(); i++)
			cout << setw(3) << v[i] << ";";
	}
};