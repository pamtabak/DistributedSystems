#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <random>
#include <limits>

using namespace std;

default_random_engine generator;
uniform_int_distribution<int> distribution(1,numeric_limits<int>::max());

int getIncreasingRandomNumber(int lastRandomNumber) 
{
	int r = distribution(generator);
	while (r <= lastRandomNumber)
	{
		r = distribution(generator);
	}	
	return r;    
}

int main(int argc, char *argv[])
{
	std::cout << "Hello World" << std::endl;

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	return 0;
}