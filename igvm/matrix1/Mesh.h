#pragma once
#include "Dote.h"
#include "Element.h"


class Mesh
{
private:
	std::vector<Element> mesh;
	std::vector<Dote> dotes;
public:
	Mesh() {}
	~Mesh() {}
	bool check(Element el, int i)
	{
		for (auto j : dotes)
			if (j == el.getNode(i))
				return false;
		return true;
	}
	void push(Element el) { 
		mesh.push_back(el); 
		for (int i = 0; i < el.getSize(); i++)
		{
			if (dotes.empty())
				dotes.push_back(el.getNode(i));
			else
				if(check(el,i))
					dotes.push_back(el.getNode(i));				
		}
	}

	double geta()
	{
		return mesh[0].getThermal_conductivity() / mesh[0].getDensity() / mesh[0].getHeat_Capacity();
	}

	Matrix createMatrixR1(double t)
	{
		vector<double> v;
		vector<unsigned> nc;
		vector<unsigned> nl;
		double h = dotes[1].getx() - dotes[0].getx();
		double a = geta();
		unsigned k = 0, n = dotes.size();
		for (int i = 0; i < n; i++)
		{
			nl.push_back(k);
			if (i == 0) {
				v.push_back(1. / t + a / h / h);
				nc.push_back(0);
				v.push_back(-a / 2 / h / h);
				nc.push_back(1);
				k += 2;
			}
			else if (i == n - 1)
			{
				v.push_back(-a / 2 / h / h);
				nc.push_back(n - 2);
				v.push_back(1. / t + a / h / h);
				nc.push_back(n - 1);
				k += 2;
			}
			else
			{
				v.push_back(-a / 2 / h / h);
				nc.push_back(i - 1);
				v.push_back(1. / t + a / h / h);
				nc.push_back(i);
				v.push_back(-a / 2 / h / h);
				nc.push_back(i + 1);
				k += 3;
			}
		}
		nl.push_back(k);
		Matrix c(k, n, v, nc, nl);
		return c;
	}

	VectorB createVectorBR1(double t, double(*u)(double), double nu1, double nu2, 
		double(*phi)(double,double))
	{
		unsigned n = dotes.size();
		double h = dotes[1].getx() - dotes[0].getx();
		double a = geta();
		vector<double> b(n);
		std::cout << "\n";
		for (int i = 0; i < n; i++)
		{
			if (i == 0)
				b[i] = nu1;
			else if (i == n - 1)
				b[i] = nu2;
			else {
				b[i] = a / 2 / h / h * u(dotes[i - 1].getx()) +
					(1. / t - a / h / h) * u(dotes[i].getx()) +
					a / 2 / h / h * u(dotes[i + 1].getx()) + phi(u(dotes[i].getx()), t);
				std::cout<<u(dotes[i].getx())<<" ";
			}
		}
		VectorB B(b);
		return B;
	}
	VectorB createVectorBR1(double t, vector<double> u, double nu1, double nu2,
		double(*phi)(double, double))
	{
		unsigned n = dotes.size();
		double h = dotes[1].getx() - dotes[0].getx();
		double a = geta();
		vector<double> b(n);
		for (int i = 0; i < n; i++)
		{
			if (i == 0)
				b[i] = nu1;
			else if (i == n - 1)
				b[i] = nu2;
			else
				b[i] = a / 2 / h / h * u[i-1] +
				(1. / t - a / h / h) * u[i] +
				a / 2 / h / h * u[i+1] + phi(u[i], t);
		}
		VectorB B(b);
		return B;
	}

	void print()
	{
		for (int i = 0; i < mesh.size(); i++)
		{
			std::cout << "[" << i << "] ";
			mesh[i].print();
			std::cout << endl;
		}
		for (auto i : dotes)
		{
			i.print();
			std::cout << "  ";
		}
	}
};