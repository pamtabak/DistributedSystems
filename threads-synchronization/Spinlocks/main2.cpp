#include <iostream>
#include <thread>  

using namespace std;


/////////////////////////////////// LOCK ///////////////////////////////////
struct lock
{
	bool held = false;
};

void acquire (lock)
{
	while (testAndSet(&lock->held));
}

void release (lock)
{
	lock->held = false;
}

/////////////////////////////////// ERROR ///////////////////////////////////

void error(char *msg)
{
    perror(msg);
    exit(1);
}

/////////////////////////////////// TEST AND SET ///////////////////////////////////

bool testAndSet (bool *flag)
{
	bool anterior = *flag;
	*flag = true;
	return anterior;
}

/////////////////////////////////// MAIN ///////////////////////////////////

// Global Variables
int totalSum;
lock spinlock;

int main(int argc, const char* argv[])
{
	if(argc != 2)
    {
        error((char *) "Wrong parameters");
    }

    int numberOfThreads = atoi(argv[1]);

    // Initializing global variables
    totalsum = 0;

    return 0;
}

int sum (int num)
{
	acquire(spinlock);
	totalSum += num;
	release(spinlock);
}