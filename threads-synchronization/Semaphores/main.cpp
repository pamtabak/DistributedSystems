#include <iostream>
#include <pthread.h>

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
}