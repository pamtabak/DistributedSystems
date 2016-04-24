#include <iostream>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 256

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

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockFileDesc, portNo, response;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;
    struct hostent *server;

    if (argc < 3)
    {
        error((char *) "ERROR obtaining address and port");
    }

    portNo = atoi(argv[2]);
    sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFileDesc < 0)
    {
        error((char *) "ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if(server == NULL)
    {
        error((char *) "ERROR no host found");
    }

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
    serverAddr.sin_port = htons(portNo);

    if(connect(sockFileDesc, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        error((char *) "ERROR connectiong to server");
    }

    while(true)
    {
        bzero(buffer, BUFFER_SIZE);
        response = read(sockFileDesc, buffer, BUFFER_SIZE - 1);
        if(response < 0)
        {
            error((char *) "ERROR reading from socket");
        }

        int n = atoi(buffer);
        if(n == 0)
        {
            break;
        }

        std::string s = isPrime(n);
        const char *c = s.c_str();
        response = write(sockFileDesc, c, s.size());
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }
    }
    close(sockFileDesc);

    return 0;
}