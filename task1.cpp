#include <omp.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int n;

void solve1()
{
	omp_set_num_threads(8);
#pragma omp parallel 
	printf("Hello world, thread: %d, amount: %d\n", omp_get_thread_num(), omp_get_num_threads());
}

void solve2()
{
	omp_set_num_threads(3);
#pragma omp parallel if(omp_get_max_threads() > 1)
	{
		printf("Hello world, thread - %d, amount: %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
	omp_set_num_threads(1);
#pragma omp parallel if (omp_get_max_threads() > 1)
	{
		printf("Hello world, thread - %d, amount: %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
}

void solve3()
{
	int a = 0, b = 0;

	omp_set_num_threads(2);
	printf("Before process 1: a = %d b = %d\n", a, b);
#pragma omp parallel private(a) firstprivate(b)
	{
		a = 0;
		a += omp_get_thread_num();
		b += omp_get_thread_num();
		printf("In process 1: a = %d b = %d\n", a, b);
	}
	printf("After process 1: a = %d b = %d\n", a, b);

	omp_set_num_threads(4);
	printf("Before process 2: a = %d b = %d\n", a, b);
#pragma omp parallel shared(a) private(b)
	{
		b = 0;
		a -= omp_get_thread_num();
		b -= omp_get_thread_num();
		printf("In process 2: a = %d b = %d\n", a, b);
	}
	printf("After process 2: a = %d b = %d\n", a, b);
}

void solve4()
{
	int a[10];
	int b[10];

	int max = -1 * RAND_MAX;
	int min = RAND_MAX;

	for (int i = 0; i < 10; i++)
	{
		a[i] = rand();
		b[i] = rand();
	}

	omp_set_num_threads(2);
#pragma omp parallel sections 
	{
#pragma omp section 
		{
			for (int i = 0; i < 10; i++)
			{
				if (a[i] < min)
				{
					min = a[i];
				}
			}
		}

#pragma omp section
		{
			for (int i = 0; i < 10; i++)
			{
				if (b[i] > max)
				{
					max = b[i];
				}
			}
		}
	}
	printf("min = %d, max = %d\n", min, max);
}

void solve5()
{
	int d[6][8];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			d[i][j] = rand();
		}
	}

#pragma omp parallel sections 
	{

#pragma omp section
		{
			int sum = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sum += d[i][j];
				}
			}
			printf("Thread: %d, avg = %d\n", omp_get_thread_num(), sum / 48);
		}

#pragma omp section
		{
			int max = -1 * RAND_MAX;
			int min = RAND_MAX;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (d[i][j] > max)
					{
						max = d[i][j];
					}
					if (d[i][j] < min)
					{
						min = d[i][j];
					}
				}
			}
			printf("Thread: %d, min = %d, max = %d\n", omp_get_thread_num(), min, max);
		}

#pragma omp section
		{
			int amount = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (d[i][j] % 3 == 0)
					{
						amount++;
					}
				}
			}
			printf("Thread: %d, amount = %d\n", omp_get_thread_num(), amount);
		}

	}
}

int main()
{
	while (true)
	{
		cin >> n;
		if (n == 1)
		{
			solve1();
		}
		if (n == 2)
		{
			solve2();
		}
		if (n == 3)
		{
			solve3();
		}
		if (n == 4)
		{
			solve4();
		}
		if (n == 5)
		{
			solve5();
		}
	}
	return 0;
}