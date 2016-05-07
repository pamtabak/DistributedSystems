#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

struct arg_struct
{
	int id;
	std::string data;
};

int8_t random(int seed, int8_t min, int8_t max)
{
	srand(seed);
	return rand() % (max - min + 1) + min;
}

void fill(int8_t *v, long n, int seed)
{
	for(long i = 0; i < n; ++i)
	{
		v[i] = random(seed, -100, 100);
	}
}

void *test(void *arguments)
{
	struct arg_struct *args = (struct arg_struct *) arguments;
	for(int i = 0; i < 10; ++i)
	{
		printf("Thread %d\n", args->id);
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 3)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	long n = atol(argv[1]);
	int k = atoi(argv[2]);

	int seed = time(NULL);

	int8_t *v = (int8_t *) malloc(n * sizeof(int8_t));
	fill(v, n, seed);

	pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
	struct arg_struct **args = (struct arg_struct **) malloc(k * sizeof(struct arg_struct *));
	for(int i = 0; i < k; ++i)
	{
		args[i] = (arg_struct *) malloc(sizeof(arg_struct));
		args[i]->id = i;
		args[i]->data = "Hello";
		pthread_create(&threads[i], NULL, test, (void *) args[i]);
	}
	for(int i = 0; i < k; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	delete [] v, threads, args;

	return 0;
}