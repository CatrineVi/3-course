#pragma once

class Color
{
	int r;
	int y;
	int b;
	int size = 3;
public:
	Color();
	Color(const Color& a);
	Color(float red, float yellow, float blue);
	~Color();

	void setR(float r);
	void setY(float y);
	void setB(float b);

	void setRandom();

	float getR() const;
	float getY() const;
	float getB() const;

	float checkR(float val);
	float checkY(float val);
	float checkB(float val);

	unsigned getSize();
	void print();
};
