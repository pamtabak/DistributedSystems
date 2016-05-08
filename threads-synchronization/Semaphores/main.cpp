#include <iostream>
#include <pthread.h>
#include <math.h>

struct arg_struct
{
	int *v;
};

bool isPrime (int number)
{
	for (int i = 2; i <= (sqrt(number) + 1); i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

int random(int min, int max)
{
	// min is 1
	// max is 10^7
	return rand() % (max - min + 1) + min;
}

void initializeVector(int *v, int n)
{
	for(int i = 0; i < n; ++i)
	{
		v[i] = 0;
	}
}

void *consume (void *arguments)
{

}

void *produce (void *arguments)
{

}

int main(int argc, char const *argv[])
{
	if(argc != 4)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	// Extracting info regarding number of threads and size of vector, passed as parameters to this program
	int Np = atoi(argv[1]);
	int Nc = atoi(argv[2]);
	int N  = atoi(argv[3]);

	// Initializing seed
	int seed = time(NULL);
	srand(seed);

	// Initializing vector, with 0 values
	int *v = (int *) malloc(N * sizeof(int));
	initializeVector(v,N);

	printf("finished initializing vector with 0\n");


	pthread_t *producerThreads = (pthread_t *) malloc(Np * sizeof(pthread_t));
	pthread_t *consumerThreads = (pthread_t *) malloc(Nc * sizeof(pthread_t));
	struct arg_struct **pArgs  = (struct arg_struct **) malloc(Np * sizeof(struct arg_struct *));
	struct arg_struct **cArgs  = (struct arg_struct **) malloc(Nc * sizeof(struct arg_struct *));

	// Create threads
	for(int i = 0; i < Np; ++i)
	{
		pthread_create(&producerThreads[i], NULL, consume, (void *) pArgs[i]);
	}
	for (int i = 0; i < Nc; ++i)
	{
		pthread_create(&consumerThreads[i], NULL, produce, (void *) cArgs[i]);
	}

	// Thread Join
	for(int i = 0; i < Np; ++i)
	{
		pthread_join(producerThreads[i], NULL);
	}
	for (int i = 0; i < Nc; ++i)
	{
		pthread_join(consumerThreads[i], NULL);	
	}

	delete [] v, producerThreads, consumerThreads;

	return 0;
}