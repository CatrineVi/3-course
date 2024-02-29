#pragma once
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
int const n = 5;

class Matrix
{
	int NN;//4
	int m;
	double j = 1.5 + 0.1 * NN;
	double k = j;
	double l = k - 0.1;
	double i;

	vector<vector<double>> matrix;/* = {
		{j * m,0.5 * j,0,0.2 * l,0},
		{0.5 * j,j,0.3 * j,0,0.1 * l},
		{0,0.3 * j,10,-0.3 * j,0.5 * l},
		{0.2 * k,0,-0.3 * j,j,-0.1 * j},
		{0,0.1 * k,0.5 * k,-0.1 * j,j * m} };*/

	vector<double> b;/* = {
		-j + 0.05 * j * j,
		-0.8 * j + 0.1 * j * j - 0.02 * l * j,
		-10 + 0.03 * j * j - 0.1 * l * j,
		-0.2 * k + 0.3 * j + 0.02 * j * j,
		0.01 * k * j - 0.5 * k - 0.2 * j * j };*/

public:
	Matrix(){};
	Matrix(int _NN, int _m, double _k)
	{
		NN = _NN;
		m = _m;
		j = 1.5 + 0.1 * _NN;
		if(_k==1 or _k==2 or _k==3 or _k==5 or _k==7 or
			_k==8 or _k==11 or _k==12)
		{
			k = j;
			l = k - 0.1;
		}
		else if (_k == 4 or _k == 9)
		{
			k = _NN; l = k;
		}
		else if (_k == 6) { k = 0; l = 0; }
		matrix = {
		{j * m,0.5 * j,0,0.2 * l,0},
		{0.5 * j,j,0.3 * j,0,0.1 * l},
		{0,0.3 * j,10,-0.3 * j,0.5 * l},
		{0.2 * k,0,-0.3 * j,j,-0.1 * j},
		{0,0.1 * k,0.5 * k,-0.1 * j,j * m} };
		b = {
		-j + 0.05 * j * j,
		-0.8 * j + 0.1 * j * j - 0.02 * l * j,
		-10 + 0.03 * j * j - 0.1 * l * j,
		-0.2 * k + 0.3 * j + 0.02 * j * j,
		0.01 * k * j - 0.5 * k - 0.2 * j * j };
	}
	Matrix(int _NN, int _k)
	{
		j = 1.5 + 0.1 * _NN;
		if (_k == 1) {
			matrix = {
				{1, 0, 0},
				{-j, 0, 2},
				{0, 2, j} };
			b = { 1 + j, -3 * j + 4, 2 * j };
		}
		else if (_k == 2) {
			matrix = {
			{- j, 0, -j},
			{-2, -j, j},
			{1, 0, 0} };
			b = {- 3 * j, 2 * j, (j - 1) };
		}

	}
	~Matrix(){};

	double getMatrix(unsigned i, unsigned j) { return matrix[i][j]; }
	double getB(unsigned i) { return b[i]; }
	vector<vector<double>> getMatrix() { return matrix; }
	vector<double> getB() { return b; }

	void print()
	{
		cout << "\nMatrix: " << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
				cout << setw(6) << matrix[i][j];
			cout << endl;
		}
	}

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
	void print(vector<double> b)
	{
		cout << "\nVector: ";
		for (int i = 0; i < b.size(); i++)
			cout << setw(11) << b[i];
	}
};