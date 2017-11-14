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

    ofstream myfile;
	string fileName = "file.txt"; 

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
        double random = randomDouble();
        unsigned int microseconds = (int) (random * 1000);
        cout << microseconds << endl;
		usleep(microseconds);
        // sleep(5.0);

        // bzero(buffer, BUFFER_SIZE);
        string request  = "request";
        const char *req = request.c_str();
        response        = write(sockFileDesc, req, request.size());
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
        string access(buffer);
        cout << access << endl;
        bzero(buffer, BUFFER_SIZE);

        // Requesting access
        std::size_t found = access.find("grant");
        if (found != std::string::npos)
        {
            // WRITE ON FILE
            string out = "I`m client with process id = " + to_string(getpid());
            writeToFile(myfile, out, fileName);

            // Release region
            string release = "release";
            const char *r  = release.c_str();
            response       = write(sockFileDesc, r, release.size());
            if(response < 0)
            {
                error((char *) "ERROR writing to socket");
            }
        }
	}

    close(sockFileDesc);

	return 0;
}