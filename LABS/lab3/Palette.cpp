#include "Palette.h"
#include "Color.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <cmath>

using namespace std;

Palette::Palette() :palette(new	Color[0]), size(0), index(0) {};

Palette::Palette(const Palette& a)
{
	palette = a.palette;
	size = a.size;
	index = 0;
}

Palette::Palette(unsigned n)
{
	palette = new Color[n];
	size = n;
	index = 0;
}

Palette::~Palette() { delete[] palette; }

void Palette::setIndex(int ind) {
	this->index = ind;
}

int Palette::getIndex() { return index; } 
int Palette::getSize() { return size; }

void Palette::ModifyElement(int index)
{
	while (true)
	{
		system("cls");
		cout << "1) enter first component \n2) enter second component"
			"\n3) enter third component \n4) random components \n0) finish changing\n";
		int choice;
		cin >> choice;
		int znach;
		if (choice == 1)
		{
			system("cls");
			cout << "R: ";
			cin >> znach;
			palette[index].setR(znach);
		}
		else if (choice == 2)
		{
			system("cls");
			cout << "Y: ";
			cin >> znach;
			palette[index].setY(znach);
		}
		else if (choice == 3)
		{
			system("cls");
			cout << "B: ";
			cin >> znach;
			palette[index].setB(znach);
		}
		else if (choice == 4)
		{
			system("cls");
			palette[index].setRandom();
		}
		else if (choice == 0)
			break;
		else
			cout << "There is no such command. Try again." << endl;
	}
}

void Palette::swapElements(Color* first, Color* second) {
	Color temp = *first;
	*first = *second;
	*second = temp;
}

void Palette::sortInAscendingOrder()
{
	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->size - i - 1; j++)
		{
			if (palette[j].getR() > palette[j + 1].getR())
				this->swapElements(&palette[j], &palette[j + 1]);

			if (palette[j].getR() == palette[j + 1].getR() &&
				palette[j].getY() > palette[j + 1].getY())
				this->swapElements(&palette[j], &palette[j + 1]);
			if (palette[j].getR() == palette[j + 1].getR() && 
				palette[j].getY() == palette[j + 1].getY() &&
				palette[j].getB() > palette[j + 1].getB())
				this->swapElements(&palette[j], &palette[j + 1]);
		}
	}
}

void Palette::sortInDescendingOreder()
{
	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->size - i - 1; j++)
		{
			if (palette[j].getR() < palette[j + 1].getR())
				this->swapElements(&palette[j], &palette[j + 1]);

			if (palette[j].getR() == palette[j + 1].getR() &&
				palette[j].getY() < palette[j + 1].getY())
				this->swapElements(&palette[j], &palette[j + 1]);
			if (palette[j].getR() == palette[j + 1].getR() &&
				palette[j].getY() == palette[j + 1].getY() &&
				palette[j].getB() < palette[j + 1].getB())
				this->swapElements(&palette[j], &palette[j + 1]);
		}
	}
}

void Palette::toRGB(int ind)
{
	float R, G, B;
	palette[ind].print();

	float i = min(palette[ind].getR()/255, palette[ind].getY()/255);
	i = min(i, palette[ind].getB()/255);
	float r = palette[ind].getR()/255 - i;
	float y = palette[ind].getY()/255 - i;
	float b = palette[ind].getB()/255 - i;
	R = r + y - min(y, b);
	G = y + 2 * min(y, b);
	B = 2 * (b - min(y, b));
	float m1 = max(R, G);
	m1 = max(m1, B);
	float m2 = max(r, y);
	m2 = max(m2, b);
	if (m2 == 0) m2 = 1;
	float n = m1 / m2;
	if (n == 0) n = 1;
	R = R / n;
	G = G / n;
	B = B / n;
	i = min(1 - palette[ind].getR()/255, 1 - palette[ind].getY()/255);
	i = min(i, 1 - palette[ind].getB()/255);
	R = ceil((R + i)*255);
	G = ceil((G + i)*255);
	B = ceil((B + i)*255);

	/*int r = palette[ind].getR()/255 * palette[ind].getR()/255 * (3 - 2*palette[ind].getR()/255);
	int y = palette[ind].getY()/255 * palette[ind].getY()/255 * (3 - 2*palette[ind].getY()/255);
	int b = palette[ind].getB()/255 * palette[ind].getB()/255 * (3 - 2*palette[ind].getB()/255);
	R = round((1 + b * (r * (0.337 + y * (-0.137)) + (-0.837 + y * (-0.163))))*255);
	G = round((1 + b * (-0.627 + y * 0.287) + r * (-1 + y * (0.5 + b * (-0.693)) - b * (-0.627)))*255);
	B = round((1 + b * (-0.4 + y * 0.6) - y + r * (-1 + b * (0.9 + y * (-1.1)) + y))*255);*/

	cout << "\nRGB: " << "(" << R << ", " << G << ", " << B << ")" << endl;
	system("pause");
}

void Palette::print()
{
	for (int i = 0; i < getSize(); i++)
	{
		cout << i + this-> index << ")";
		palette[i].print();
		cout << endl;
	}
}

