#include "Matrix.h";
#include "VectorB.h";
#include "Solver.h";

int main()
{
	Matrix m;
	m.read();
	m.print();
	VectorB b;
	b.calculationVectorB(m);
	b.print();
	Solver x;
	x.Gauss(m, b);
	x.Jacobi(m, b);
	return 0;
}