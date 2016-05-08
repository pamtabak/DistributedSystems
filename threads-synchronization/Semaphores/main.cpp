#include <iostream>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

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

void *consume (void *arguments)
{
	while (true)
	{
		wait(full); // Wait for a full buffer
		wait(mutex);
		// Remove resource from a full buffer
		// Copy value from buffer, and set it to 0
		// Verify if this number is prime
		// printf(...)
		signal(mutex);
		signal(full);
		// Consume resource
	}
}

void *produce (void *arguments)
{
	while (true)
	{
		// Produce new number
		wait(empty); // Verify if array is full
		wait(mutex); // Write on shared vector
		// Add resource to an empty buffer
		signal(mutex);
		signal(empty);
	}
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
	int *v = (int *) calloc(0,N * sizeof(int));

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