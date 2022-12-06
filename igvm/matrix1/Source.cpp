#include "Matrix.h";
#include "VectorB.h";
#include "Solver.h";

int main()
{
	Matrix m;
	//string file = "Test_int.mtx";
	//string file = "nos4.mtx";
	string file = "Trefethen_500.mtx";
	//string file = "msc01050.mtx";
	//string file = "Trefethen_2000.mtx";
	m.read(file);
	//m.print();
	VectorB b;
	b.calculationVectorB(m);
	//b.print();
	Solver x;
	x.Gauss(m, b);
	x.Jacobi(m, b);
	x.Zeidel(m, b);
	x.fastestDescent(m, b);

	return 0;
}