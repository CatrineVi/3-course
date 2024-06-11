#include <cstdio>
#include <iostream>
#include <omp.h>
using namespace std;

void Scalar(const int count)
{
	double* a = new double[count];
	double* b = new double[count];
	double ab = 0, ab1 = 0;
	for (int i = 0; i < count; i++)
	{
		a[i] = 1; b[i] = 1;
	}
	double t1 = omp_get_wtime();
	for (int i = 0; i < count; i++)
		ab1 += a[i] * b[i];
	t1 = omp_get_wtime() - t1;
	printf("ab:%.8le time:%le\n", ab1, t1);

	int NoT = 4;
	double t = omp_get_wtime();
#pragma omp parallel num_threads(NoT) reduction(+:ab)
	{
		//int thread = omp_get_thread_num();
		//int NoTlocal = omp_get_num_threads();
#pragma omp for schedule(dynamic,10)
		for (int i = 0; i < count; i++)
			ab += a[i] * b[i];
	}
	t = omp_get_wtime() - t;
	printf("ab_parallel:%.8le time_parallel:%le", ab, t);
	delete[]a;
	delete[]b;
}
int main()
{
	const int count = 120000001;
	Scalar(count);
	return 0;
}