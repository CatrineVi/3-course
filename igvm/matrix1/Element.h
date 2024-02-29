#pragma once
#include "Dote.h"
#include <vector>

class Element
{
protected:
	std::vector<Dote> el;
	double thermal_conductivity; //коэф теплопроводности
	double heat_capacity; //удельной теплоемкости
	double density; //плотность
public:
	Element():thermal_conductivity(0),heat_capacity(0){}
	Element(std::vector<Dote> _el)
	{
		el = _el;
	}
	Element(const unsigned n) :el(n) { }
	~Element(){}
	void setThermal_conductivity(double _tc) { thermal_conductivity = _tc; }
	void setHeat_Capacity(double _hc) { heat_capacity = _hc; }
	void setDensity(double _d) { density = _d; }
	double getThermal_conductivity() { return thermal_conductivity; }
	double getHeat_Capacity() { return heat_capacity; }
	double getDensity() { return density; }
	unsigned getSize() { return el.size(); }
	Dote& newNode(unsigned i) { 
		return el[i]; }
	Dote getNode(unsigned i) {
		return el[i];
	}
	void print()
	{
		for (int i = 0; i < el.size(); i++)
		{
			el[i].print();
			std::cout << " ";
		}
	}
};

class Section : public Element
{
private:
	static const unsigned size = 2;
public:
	Section():Element(size) {}
	Section(double x1, double x2):Element(size) { newNode(0) = Dote(x1); newNode(1) = Dote(x2); }
	~Section() {}
};

class Triangle : public Element
{
private:
	const unsigned size = 3;
public:
	Triangle():Element(size) {}
	Triangle(double x1, double x2, double x3) { getNode(0) = Dote(x1); getNode(1) = Dote(x2); getNode(2) = Dote(x3); }
	~Triangle() {}
};

class Square : public Element
{
private:
	const unsigned size = 4;
};

class Tetrahedron :public Element
{
private:
	const unsigned size = 4;
};

class Cube : public Element
{
private:
	const unsigned size = 8;
};
