#include <iostream>
#include <vector>

using namespace std;

double d = -3, q = -4.67;
int N = 5;
vector<vector<double>> A = { 
	{q,1,0,0,0},
	{1,-2,1,0,0},
	{0,1,-2,1,0},
	{0,0,1,-2,1},
	{0,0,0,1,q} };
vector<double> b = { 0,d,d,d,0 };

int main()
{
	vector<double> P = {0,1,1,1,1}; 
	vector<double> Q = {q,-2,-2,-2,q}; 
	vector<double> R = {1,1,1,1,0}; 
	vector<double> D = {0,d,d,d,0}; 
	vector<double> X(N);
	vector<double> s(N);
	s[0] = -R[0] / Q[0];
	vector<double> n(N);
	n[0] = D[0] / Q[0];
	for (int i = 1; i < N - 1; i++)
	{
		double z = Q[i] + P[i] * s[i - 1];
		s[i] = -R[i] / z;
		n[i] = (D[i] - P[i] * n[i - 1]) / z;
	}
	X[N - 1] = (D[N - 1] - P[N - 1] * n[N - 2]) / (Q[N - 1] + P[N - 1] * s[N - 2]);
	for (int i = N - 2; i >= 0; i--)
		X[i] = s[i] * X[i + 1] + n[i];
	for (int i = 0; i < X.size(); i++)
		cout << X[i] << "  ";
	cout << endl;
	vector<double> r(N);
	r[0] = D[0] - Q[0] * X[0] - R[0] * X[1];
	for (int i = 1; i < N - 1; i++)
		r[i] = D[i] - P[i] * X[i - 1] - Q[i] * X[i] - R[i] * X[i + 1];
	r[N - 1] = D[N - 1] - P[N - 1] * X[N - 2] - Q[N - 1] * X[N - 1];
	for (int i = 0; i < N; i++)
		cout << r[i] << "   ";
	return 0;
}