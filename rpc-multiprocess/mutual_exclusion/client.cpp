#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <math.h>
#include <chrono>
#include <string>
#include <fstream>

#define T 1
#define X 100
#define Y 1

using namespace std;

void writeToFile (ofstream &file, string text, string fileName)
{
	file.open (fileName, fstream::app);
	file << text << "\n";
	file.close();
}

int random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		std::cout << "Wrong parameters" << std::endl;
		exit(-1);
	}

	int K       = atoi(argv[1]);
	
	// int arrival = atoi(argv[2]); // DUVIDA: Essa info nao pode ficar no cliente.. Talvez no coordenador?
	// porque nao sao threads dessa vez, sao processos diferentes
	// if arrival = 0: bulk arrival
	// if arrival = 1: sequential arrival

	return 0;
}