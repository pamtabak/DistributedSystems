#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <climits>
#include <chrono>
#include <math.h>

using namespace std;

chrono::high_resolution_clock::time_point startTime;

struct args
{
	int rangeFrom;
	int rangeTo;
};

int random(int min, int max)
{
	// min is 1
	// max is 10^7
	return rand() % (max - min + 1) + min;
}

void *test(void *args)
{

}

int main(int argc, const char* argv[])
{
	startTime = chrono::high_resolution_clock::now();
	
	if(argc != 3)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	// Extracting info regarding number of threads and size of vector, passed as parameters to this program
	int n = atoi(argv[1]); // vector size
	int k = atoi(argv[2]); // number of threads

	// Initializing seed
	int seed = time(NULL);
	srand(seed);

	// Initializing vector
	int *v = new int[n];
	for (int i = 0; i < n; i++)
	{
		v[i] = random(1, INT_MAX);
	}

	// Creating threads
	pthread_t *threads = (pthread_t *) malloc(k * sizeof(pthread_t));
	struct args **tArgs  = (struct args **) malloc(k * sizeof(struct args *));
	int delta = n / k;
	int lastValue = 0;
	for (int i = 0; i < k; i++)
	{
		tArgs[i]            = (args *) malloc(sizeof(args));
		tArgs[i]->rangeFrom = lastValue;
		tArgs[i]->rangeTo   = lastValue + delta;
		

		lastValue += delta;
		if (i == (k - 1))
		{
			tArgs[i]->rangeTo = n;
		}

		pthread_create(&threads[i], NULL, test, (void *) tArgs[i]);
	}

	// Thread Join
	for(int i = 0; i < k; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	delete [] v, threads;

	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> endTimeSpan              = chrono::duration_cast<chrono::duration<double> >(endTime - startTime);
	printf("end: %lf secs\n", endTimeSpan.count());

	return 0;
}
