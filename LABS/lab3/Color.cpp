#include "Color.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

Color::Color()
{
	setR(0);
	setY(0);
	setB(0);
}

Color::Color(const Color& a)
{
	setR(a.getR());
	setY(a.getY());
	setB(a.getB());
}

Color::Color(float r, float y, float b)
{
	setR(checkR(r));
	setY(checkY(y));
	setB(checkB(b));
}

Color::~Color(){}

unsigned Color::getSize() { return this->size; }

void Color::print() { cout << "(" << this->r << "," << this->y << "," << this->b << ")"; }

void Color::setR(float r) { this->r = checkR(r); }
void Color::setY(float y) { this->y = checkY(y); }
void Color::setB(float b) { this->b = checkB(b); }

void Color::setRandom()
{
	srand(time(0));
	this->r = rand() % 255;
	this->y = rand() % 255;
	this->b = rand() % 255;
}

float Color::getR()const { return this->r; }
float Color::getY()const { return this->y; }
float Color::getB()const { return this->b; }

float Color::checkR(float val)
{
	while (val < 0 || val > 255)
	{
		cout << "Error! Try again: ";
		cin >> val;
	}
	return val;
}

float Color::checkY(float val)
{
	while (val < 0 || val > 255)
	{
		cout << "Error! Try again: ";
		cin >> val;
	}
	return val;
}

float Color::checkB(float val)
{
	while (val < 0 || val > 255)
	{
		cout << "Error! Try again: ";
		cin >> val;
	}
	return val;
}