#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include <chrono>

struct arg_struct
{
	int8_t *v;
	long n;
	int k;
	long c;
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
	for(long i = args->c; i < args->n; i += args->k)
	{
		pSum += (int) args->v[i];
	}
	acquire(args->spinlock);
	*args->tSum += pSum;
	release(args->spinlock);
}

int main(int argc, char const *argv[])
{
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	// clock_t startTime = clock();

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

	std::chrono::high_resolution_clock::time_point fillTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> fillTimeSpan = std::chrono::duration_cast< std::chrono::duration<double> >(fillTime - startTime);
	std::cout << "fill: " << fillTimeSpan.count() << " secs" << std::endl;
	// clock_t fillTime = clock();
 	// std::cout << "fill: " << double(fillTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;

	struct lock spinlock;
	long tSum = 0;
	pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
	struct arg_struct **args = (struct arg_struct **) malloc(k * sizeof(struct arg_struct *));
	long c = 0;
	for(int i = 0; i < k; ++i)
	{
		args[i] = (arg_struct *) malloc(sizeof(arg_struct));
		args[i]->v = v;
		args[i]->n = n;
		args[i]->k = k;
		args[i]->c = c;
		args[i]->tSum = &tSum;
		args[i]->spinlock = &spinlock;
		pthread_create(&threads[i], NULL, sum, (void *) args[i]);
		c++;
	}
	for(int i = 0; i < k; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	delete [] v, threads, args;

	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> endTimeSpan = std::chrono::duration_cast< std::chrono::duration<double> >(endTime - startTime);
	std::cout << "end: " << endTimeSpan.count() << " secs" << std::endl;
	// clock_t endTime = clock();
    // std::cout << "end: " << double(endTime - startTime) / (double)CLOCKS_PER_SEC << " secs" << std::endl;

	return 0;
}