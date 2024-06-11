#include <cstdio>
#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
	const int count = 2001;
	double* array = new double[count];
	double sum = 0;
	for (int i = 0; i < count; i++)
		array[i] = 1;
	int NoT = 1;
	double t = omp_get_wtime();
#pragma omp parallel num_threads(NoT) reduction(+:sum)
	{
		int thread = omp_get_thread_num();
		int index = thread;
		int NoTlocal = omp_get_num_threads();
		
		while (index < count) {
			sum += array[index];
			index += NoTlocal;
		}
	}
	t = omp_get_wtime() - t;
	printf("sum: %le T_%d: %le", sum, NoT, t);
	delete[]array;
	return 0;
}
//omp_get_wtick() = time of tick