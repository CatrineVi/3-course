#pragma once

class Dote
{
private:
	double x;
	double y;
	double z;
public: 
	Dote(){}
	Dote(double _x)
	{
		x = _x;
		y = 0;
		z = 0;
	}
	Dote(double _x, double _y)
	{
		x = _x;
		y = _y;
		z = 0;
	}
	Dote(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	~Dote() {}
	double getx()
	{
		return x;
	}
	double gety()
	{
		return y;
	}
	double getz()
	{
		return z;
	}
	void print()
	{
		std::cout << "(" << x << "; " << y << "; " << z << ")";
	}
	bool operator==(const Dote& d)
	{
		if (x == d.x && y == d.y && z == d.z)
			return true;
		return false;
	}
	bool operator!=(Dote& d)
	{
		if (x == d.x && y == d.y && z == d.z)
			return false;
		return true;
	}
};