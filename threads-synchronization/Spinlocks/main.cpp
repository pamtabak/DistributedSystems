#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <atomic>

struct arg_struct
{
	int8_t *v;
	long min;
	long max;
	long *tSum;
	struct lock *spinlock;
};

struct lock
{
	bool held = 0;
};

void acquire(struct lock *spinlock)
{
	while(__sync_lock_test_and_set(&spinlock->held, 1));
}

void release (struct lock *spinlock)
{
	spinlock->held = 0;
}

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

void *sum(void *arguments)
{
	struct arg_struct *args = (struct arg_struct *) arguments;
	long pSum = 0;
	for(long i = args->min; i < args->max; ++i)
	{
		pSum += (int) args->v[i];
	}
	acquire(args->spinlock);
	*args->tSum += pSum;
	release(args->spinlock);
}

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	// Extracting info regarding number of threads, passed as parameters to this program
	long n = atol(argv[1]);
	int k  = atoi(argv[2]) < n ? atoi(argv[2]) : (int) n;

	// Initializing seed
	int seed = time(NULL);
	srand(seed);

	int8_t *v = (int8_t *) malloc(n * sizeof(int8_t));
	fill(v, n);

	printf("finished filling vector\n");

	struct lock spinlock;

	long tSum = 0;
	for (long i = 0; i < n; ++i)
	{
		tSum += (int) v[i];
	}
	printf("real total sum: %ld\n", tSum);

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
		args[i]->spinlock = &spinlock;
		pthread_create(&threads[i], NULL, sum, (void *) args[i]);
		min = max;
		max = min + delta;
		if (i == k - 2) { max = n; }	// in case n % k != 0
	}
	for(int i = 0; i < k; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	delete [] v, threads, args;

	printf("test total sum: %ld\n", testSum);

	return 0;
}