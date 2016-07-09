#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


class Lock
{
public:	
	bool held = 0;

	void acquire()
	{
	    while(__sync_lock_test_and_set(&this->held, 1));
	}

	void release ()
	{
	    this->held = 0;
	}
};