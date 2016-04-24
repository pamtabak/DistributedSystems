#include <iostream>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

std::string isPrime (int number)
{
    for (int i = 2; i <= (sqrt(number) + 1); i++)
    {
        if (number % i == 0)
        {
            return "false";
        }
    }
    return "true";
}

int main(int argc, char *argv[])
{
    return 0;
}