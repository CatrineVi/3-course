//f = e^(x+y)
//phi = 3e^x + y^2(1-x)
#include <iostream>
#include <vector>

int a = 1;
double e = 2.7182818285;

double f(double x, double y)
{
	return pow(e, x + y);
}
double phi(double x, double y)
{
	return 3 * pow(e, x) + y * y * (1 - x);
}

