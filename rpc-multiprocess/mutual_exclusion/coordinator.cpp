#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <fstream>
#include <string>

#include <chrono>
#include <ctime>
#include <ratio>

#include <pthread.h>

using namespace std;

// g++ main.cpp -o main.out -std=c++11

void writeToFile (ofstream &myfile, string text, string fileName)
{
	myfile.open (fileName, fstream::app);
	myfile << text << "\n";
	myfile.close();
}

int main(int argc, const char* argv[])
{
	// get RTC (real time clock)
	using chrono::system_clock;
	system_clock::time_point today = system_clock::now(); 

	time_t tt;
  	tt = system_clock::to_time_t(today);
  	cout << "today is: " << ctime(&tt);


	// Writing to a file
	// ofstream myfile;
	// writeToFile(myfile, "oie", "log.txt");
	return 0;
}