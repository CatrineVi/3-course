#pragma once
#include "Color.h"
#include <vector>

class Palette
{
	Color* palette;
	unsigned size;
	int index;
public:
	Palette();
	Palette(const Palette& a);
	Palette(unsigned n);
	~Palette();

	void setIndex(int ind);
	int getIndex();
	int getSize();
	void swapElements(Color* first, Color* second);
	void sortInAscendingOrder();
	void sortInDescendingOreder();
	void toRGB(int ind);
	void ModifyElement(int ind);
	void print();
};