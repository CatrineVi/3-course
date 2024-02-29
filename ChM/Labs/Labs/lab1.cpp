#include "Matrix.h"
#include "Solver.h"

int main()
{

	Matrix m(4,1,1);//1,2,3,5,7,8,11,12
	//m.print();
	Solver x;
	x.Gauss(m);
	x.Gordan_Gauss(m);
	x.LU(m);

	Matrix m4(4, 1, 4);//4,9
	//m4.print();
	x.Holez(m4);

	x.Ortogonal(m);

	Matrix m6(4, 1, 6);//6
	//m6.print();
	x.Progonka(m6);

	x.ProstIter(m);
	x.Jacobi(m);
	x.Zeidel(m4);

	Matrix mk1(4, 1);
	Matrix mk2(4, 2);
	x.Complex(mk1, mk2);
	return 0;
}