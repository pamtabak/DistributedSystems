#include <iostream>
#include <random>
#include <limits>
#include <string>
#include <math.h>

#define String_Size 100

using namespace std;

default_random_engine generator;
uniform_int_distribution<int> distribution(1,numeric_limits<int>::max());

int getIncreasingRandomNumber(int lastRandomNumber) 
{
	int r = distribution(generator);
	while (r <= lastRandomNumber)
	{
		r = rand();
	}	
	return r;    
}

string isPrime (int number)
{
	for (int i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
		{
			return "false";
		}
	}
	return "true";
}

int main(int argc, const char* argv[])
{
	if(argc != 2)
    {
        cout << "Wrong parameters." << endl;
        return EXIT_FAILURE;
    }

    int pipeFileDescriptors[2];

    int indexOfZero = atoi(argv[1]);

    char readPipe[100];

	/* The function pipe() creates the pipe and return 2 file descriptors. 
	This operation is done before the fork so that both processes will 
	know about the same pipe, which will allow them to communicate.  */
	int status = pipe(pipeFileDescriptors); 

	// Sanity Check
	if (status == -1)
	{
		// Something went wrong
		perror("Trouble when creating pipe.");
		exit(1);
	}

	/* The function fork() creates the child process */
    int pid = fork();

    // Sanity Checks
    if (pid == -1)
    {
    	// Something went wrong
    	perror("Trouble when creating the child process");
		exit(2);
    }
    else if (pid == 0)
    {
    	// Child : sends message to parent
    	// This is the write end

		int lastRandomNumber = 0;
    	for (int i = 0; i < indexOfZero; i++) {
    		int r =  getIncreasingRandomNumber(lastRandomNumber);
    		lastRandomNumber = r;
    		const char * c = to_string(r).c_str();
    		string number = c;
    		cout << "About to send number: " + number << endl;
    		write(pipeFileDescriptors[1], c, number.size() + 1);
    		sleep(2);
    	}

    	// When it`s over, send 0
    	cout << "It's over. Sending 0" << endl;
    	write(pipeFileDescriptors[1], "0", 2); 

    	close(pipeFileDescriptors[1]);
		exit(0);
    }
    else
    {
    	// Parent : receives message from child

    	// This is the read end
  //   	read(pipeFileDescriptors[0], readPipe, String_Size);

		// string numericString = readPipe; // readPipe is char
		// int number = atoi(numericString.c_str());
		// int lastNumber;

		// cout << "Just received a message that says: " + numericString << endl;

		// string prime = isPrime(number);
		// cout << "Number " + numericString + " is prime: " + prime << endl;
		// int number = 1;

		while (true)
		{
			read(pipeFileDescriptors[0], readPipe, String_Size);

			string numericString = readPipe; // readPipe is char
			int number = atoi(numericString.c_str());
			
			if (number == 0)
			{
				break;
			}

			cout << "Just received a message that says: " + numericString << endl;

			string prime = isPrime(number);
			cout << "Number " + numericString + " is prime: " + prime << endl;
		}

		cout << "Consumer just received 0. Finishing process" << endl;
		close(pipeFileDescriptors[0]);
		exit(0);
    }
}