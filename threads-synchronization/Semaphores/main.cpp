#include <iostream>
#include <pthread.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
// #include <semaphore.h>
// #include <mutex>
// #include <condition_variable>


/* Missing:
	- check empty
	- check full
	- consume
	- stop program
*/

struct arg_struct
{
	int *v;
	int *vSize;
	long *numbersConsumed;
	sem_t *empty;
	pthread_mutex_t *arrayMutex;
	pthread_mutex_t *variableMutex;
	sem_t *full;
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
	struct arg_struct *args = (struct arg_struct *) arguments;
	while (true)
	{
		// In this procedure, we need to update the amount of numbers already consumed
		if (*args->numbersConsumed == 0)
		{
			exit(0); // STOP PROGRAM
		}

		sem_wait(args->full); // Wait for a full buffer
		pthread_mutex_lock(args->arrayMutex);
		pthread_mutex_lock(args->variableMutex);
		(*args->numbersConsumed)--;
		int toBeConsumed;
		for(int i = 0; i < *args->vSize; i++)
		{
			if(args->v[i] != 0)
			{
				// Remove resource from a full buffer
				toBeConsumed = args->v[i];
				args->v[i] = 0;
				break;
			}
		}
		// Consume resource
		printf("The number %d is %s prime.\n", toBeConsumed, isPrime(toBeConsumed) ? "" : "not");
		pthread_mutex_unlock(args->variableMutex);
		pthread_mutex_unlock(args->arrayMutex);
		sem_post(args->empty);
	}
}

void *produce (void *arguments)
{
	struct arg_struct *args = (struct arg_struct *) arguments;
	while (true)
	{
		// Produce new number
		int randomNumber = random(1,1000000);

		sem_wait(args->empty); // Verify if array is full
		pthread_mutex_lock(args->arrayMutex); // Write on shared vector

		// Add resource to an empty buffer
		for(int i = 0; i < *args->vSize; i++)
		{
			if(args->v[i] == 0)
			{
				args->v[i] = randomNumber;
			}
		}
		pthread_mutex_unlock(args->arrayMutex);
		sem_post(args->full);
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 5)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	// Extracting info regarding number of threads and size of vector, passed as parameters to this program
	int Np = atoi(argv[1]);
	int Nc = atoi(argv[2]);
	int N  = atoi(argv[3]);
	long C = atol(argv[4]); // number of times Consumer will have to consume some number	

	// Initializing mutex
	pthread_mutex_t arrayMutex    = PTHREAD_MUTEX_INITIALIZER; // control access to array
	pthread_mutex_t variableMutex = PTHREAD_MUTEX_INITIALIZER; // control access to variable that checks the number of numbers consumed
	
	// Initializing semaphores
	
	sem_t empty;
	sem_t full;
	
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);

	// pthread_mutex_t numbersConsumed = PTHREAD_MUTEX_INITIALIZER;
	// pthread_mutex_t empty           = PTHREAD_MUTEX_INITIALIZER;
	// pthread_mutex_t full            = PTHREAD_MUTEX_INITIALIZER;

	// pthread_mutex_init(&numbersConsumed, NULL);
	// pthread_mutex_init(&empty, NULL);
	// pthread_mutex_init(&mutex, NULL);
	// pthread_mutex_init(&full, NULL);

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
		pArgs[i]                  = (arg_struct *) malloc(sizeof(arg_struct));
		pArgs[i]->v               = v;
		pArgs[i]->vSize			  = &N;
		pArgs[i]->numbersConsumed = &C;
		pArgs[i]->empty           = &empty;
		pArgs[i]->arrayMutex      = &arrayMutex;
		pArgs[i]->variableMutex   = &variableMutex;
		pArgs[i]->full            = &full;
		pthread_create(&producerThreads[i], NULL, produce, (void *) pArgs[i]);
	}
	for (int i = 0; i < Nc; ++i)
	{
		cArgs[i]                  = (arg_struct *) malloc(sizeof(arg_struct));
		cArgs[i]->v               = v;
		cArgs[i]->vSize			  = &N;
		cArgs[i]->numbersConsumed = &C;
		cArgs[i]->arrayMutex      = &arrayMutex;
		cArgs[i]->variableMutex   = &variableMutex;
		cArgs[i]->full            = &full;
		pthread_create(&consumerThreads[i], NULL, consume, (void *) cArgs[i]);
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