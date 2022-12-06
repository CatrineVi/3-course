#include<iostream>
#include "Palette.h"
#include "Modify.h"

using namespace std;

int main()
{
	cout << "How many colors are in the palette: ";
	unsigned n;
	cin >> n;
	Palette p(n);
	modifyPalette(p);
	return 0;
}