#include "Matrix.h";
#include "VectorB.h";
#include "Solver.h";
#include "Mesh.h"

double u(double x)
{
	return sin(x);
}
double phi(double x, double t)
{
	return 0;
}

int main()
{
	//Matrix m;
	//string file = "test3.mtx";
	//string file = "Test_int.mtx";
	//string file = "nos4.mtx";
	//string file = "Trefethen_500.mtx";
	//string file = "msc01050.mtx";
	//string file = "Trefethen_2000.mtx";
	//m.read(file);
	//m.print(); cout << endl;
	//m.print(m.getMatrixM1());
	//m.newEl(55, 1, 0);
	//m.print(); cout << endl;// << m.getKol_Nenul();
	//Matrix c;// (10);
	//c.newEl(55, 0, 0);
	//c.newEl(15, 2, 3);
	//c.newEl(5, 2, 4);
	//c.print(); cout << endl << c. getKol_Nenul();
	//VectorB b;
	//b.calculationVectorB(m);
	//b.print();
	//Solver x;
	//x.Gauss(m, b);
	//x.Jacobi(m, b);
	//x.Zeidel(m, b);
	//x.fastestDescent(m, b);

	/*vector<double> v{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
	x.ortoArnald(m, 5, v);*/
	//x.FOM(m, b, 5);
	//x.CG(m, b);
	//x.GMRES(m, b, 10);
	//x.P_FOM(m, b, 5);
	//x.P_CG(m, b);
	//x.AISM_FOM(m, b, 5);
	//x.productAB(m, m);
	//Matrix a;
	//string file1 = "test3.2.mtx";
	//a.read(file1);
	//a.print(); cout << endl;
	//a.print(a.getMatrixM1());
	//Matrix c = m + m;
	//c.print();
	
	Mesh mesh; double t = 1e+1;
	for (double i = 0; i < 0.9; i+= 0.1)
	{
		Section s(i, i + 0.1);
		s.setThermal_conductivity(46.);
		s.setHeat_Capacity(460.);
		s.setDensity(7800.);
		mesh.push(s);
	}	
	mesh.print();
	Matrix A = mesh.createMatrixR1(t);
	A.print();
	VectorB b = mesh.createVectorBR1(t, u, -20, 50, phi);
	b.print();
	Solver x;
	int it = 0, k = 10000;
	while (it < k)
	{
		b = mesh.createVectorBR1(t, x.CG(A, b), -20, 50, phi);
		it++;
	}
	b.print();

	return 0;
}