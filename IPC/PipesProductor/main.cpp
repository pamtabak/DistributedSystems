#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <string>
#include <limits>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,std::numeric_limits<int>::max());

int getIncreasingRandomNumber(int lastRandomNumber) 
{
	int r = distribution(generator);
	while (r <= lastRandomNumber)
	{
		r = rand();
	}	
	return r;    
}

int main(int argc, const char* argv[])
{
	if(argc != 2)
    {
        std::cout << "Wrong parameters." << std::endl;
        return EXIT_FAILURE;
    }

    int indexOfZero = atoi(argv[1]);

    int lastRandomNumber = 0;
    for (int i = 0; i < indexOfZero; i++) {
    	int r =  getIncreasingRandomNumber(lastRandomNumber);
    	std::cout << r << std::endl;
    	lastRandomNumber = r;
    }

    // send number Zero to Consumer

    // gerar numeros aleatorios e crescentes

}