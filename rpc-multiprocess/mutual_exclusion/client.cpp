#include <stdio.h>
#include <stdlib.h>
// #include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

#include <chrono>
#include <ctime>
#include <ratio>

#define T 1
#define X 100

using namespace std;

void writeToFile (ofstream &file, string text, string fileName)
{
	file.open (fileName, fstream::app);
	file << text << "\n";
	file.close();
}

// returns random double number [0,1]
long random()
{
	return (long) rand() / (RAND_MAX);
}

int main(int argc, const char* argv[])
{
	srand(getpid());

	int numberOfLinesWriten = 0;

	while (numberOfLinesWriten < X)
	{

	}

	return 0;
}