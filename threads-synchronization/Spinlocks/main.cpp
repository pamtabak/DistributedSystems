#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

struct arg_struct
{
	int8_t *v;
	long min;
	long max;
	long *tSum;
};

int8_t random(int8_t min, int8_t max)
{
	return rand() % (max - min + 1) + min;
}

void fill(int8_t *v, long n)
{
	for(long i = 0; i < n; ++i)
	{
		v[i] = random(-100, 100);
	}
}

void *test(void *arguments)
{
	struct arg_struct *args = (struct arg_struct *) arguments;
	long pSum = 0;
	for(long i = args->min; i < args->max; ++i)
	{
		pSum += (int) args->v[i];
	}
	// begin critical_section
	*args->tSum += pSum;
	// end critical_section

}

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	long n = atol(argv[1]);
	int k  = atoi(argv[2]) < n ? atoi(argv[2]) : (int) n;

	int seed = time(NULL);
	srand(seed);

	int8_t *v = (int8_t *) malloc(n * sizeof(int8_t));
	fill(v, n);

	printf("finished filling vector\n");

	long tSum = 0;
	for (long i = 0; i < n; ++i)
	{
		tSum += (int) v[i];
	}
	printf("real total sum: %d\n", tSum);

	long testSum = 0;

	pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
	struct arg_struct **args = (struct arg_struct **) malloc(k * sizeof(struct arg_struct *));
	long min, max, delta;
	delta = n / k;
	min = 0;
	max = delta;
	for(int i = 0; i < k; ++i)
	{
		args[i] = (arg_struct *) malloc(sizeof(arg_struct));
		args[i]->v = v;
		args[i]->min = min;
		args[i]->max = max;
		args[i]->tSum = &testSum;
		pthread_create(&threads[i], NULL, test, (void *) args[i]);
		min = max;
		max = min + delta;
	}
	for(int i = 0; i < k; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	delete [] v, threads, args;

	printf("test total sum: %d\n", testSum);

	return 0;
}