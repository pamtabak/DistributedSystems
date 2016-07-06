#include <stdio.h>
#include <stdlib.h>
// #include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <strings.h>

#include <chrono>
#include <ctime>
#include <ratio>


#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 256
#define PORT_NO 12345
#define MAX_CONNECTIONS 5

#define T 1
#define X 100

using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void writeToFile (ofstream &file, string text, string fileName)
{
	file.open (fileName, fstream::app);
	file << text << "\n";
	file.close();
}

// returns random double number [0,1]
double randomDouble()
{
	return (double) (rand()) / (RAND_MAX);
}

int main(int argc, const char* argv[])
{
	srand(getpid());

	string fileName      = "file.txt"; 

	// Connecting to server
	int sockFileDesc, portNo, response;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;
    struct hostent *server;

    sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(sockFileDesc < 0)
    {
        error((char *) "ERROR opening socket");
    }

    server = gethostbyname("localhost");
    if(server == NULL)
    {
        error((char *) "ERROR no host found");
    }

    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
    serverAddr.sin_port = htons(PORT_NO);

    if(connect(sockFileDesc, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        error((char *) "ERROR connectiong to server");
    }

	for (int i = 0; i < X; i++)
	{
		sleep(randomDouble());

        bzero(buffer, BUFFER_SIZE);

        string s      = "request";
        const char *c = s.c_str();
        response      = write(sockFileDesc, c, s.size());
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }

        // Wait for coordinator`s answer
        response = read(sockFileDesc, buffer, BUFFER_SIZE - 1);
        if(response < 0)
        {
            error((char *) "ERROR reading from socket");
        }

        // Just checking if coordinator has granted this client access
        std::string access(buffer);

        // Requesting access
        std::size_t found = access.find("grant");
        if (found != std::string::npos)
        {
            // WRITE ON FILE
            std::cout << "granted" << std::endl;
        }

        // Release region
        bzero(buffer, BUFFER_SIZE);

        s        = "release"; // release
        c        = s.c_str();
        response = write(sockFileDesc, c, s.size());
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }
	}

	close(sockFileDesc);

	return 0;
}