#include <iostream>
#include <vector>

int l = 8;
double a = 0.5, u0 = 0, ul = 1;
double f(double x)
{
	return sin(x);
}

double h = 1, T = 0.5*h/a/a;


void print(std::vector<double> v)
{
	for (auto i : v)
		std::cout << i << "  ";
}
int main()
{
	std::vector<std::vector<double>> v(l + 1);
	for (int i = 0; i < v.size(); i++)
	{
		if (i == 0) v[i].push_back(u0);
		else if (i == l) v[i].push_back(ul);
		else v[i].push_back(f(i));
	}
	for (double t = T; t <= T * 10; t += T)
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (i == 0) v[i].push_back(u0);
			else if (i == l) v[i].push_back(ul);
			else v[i].push_back(v[i][v[i].size()-1]+
				a*a*T/h/h*(v[i+1][v[i+1].size()-1]-
					2* v[i][v[i].size() - 1]+ v[i-1][v[i-1].size() - 1]));
		}
	}

	for (auto i : v)
	{
		print(i);
		std::cout << std::endl;
	}
}


