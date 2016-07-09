#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <fstream>
#include <string>
#include <strings.h>

#include <chrono>
#include <ctime>
#include <ratio>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

#include "lock.hpp"

#define BUFFER_SIZE 256
#define PORT_NO 12345
#define MAX_CONNECTIONS 1000

// g++ main.cpp -o main.out -std=c++11

std::vector<int> processLine;
Lock lock;

struct arg_struct
{
    int *sockFileDesc;
    struct sockaddr_in * clientAddr;

};

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void writeToFile (std::ofstream &myfile, std::string text, std::string fileName)
{
	myfile.open (fileName, std::fstream::app);
	myfile << text << "\n";
	myfile.close();
}

void doTheJob (int newSockFileDesc)
{
    char buffer[BUFFER_SIZE];
    int response;

    // while (true)
    while (read(newSockFileDesc, buffer, BUFFER_SIZE - 1) > 0)
    {
        // bzero(buffer, BUFFER_SIZE);
        // response = read(newSockFileDesc, buffer, BUFFER_SIZE - 1); // request to write on file
        // if(response < 0)
        // {
        //     error((char *) "ERROR reading from socket");
        // }
        // else if (response == 0)
        // {
        //     // client has closed its connection
        //     break;
        // }

        std::string access(buffer);
        bzero(buffer, BUFFER_SIZE);

        // Requesting access
        std::size_t found = access.find("request");
        if (found != std::string::npos)
        {
            // lock.acquire();
            if (processLine.size() == 0)
            {
                // Queue is empty
                response = write(newSockFileDesc, "grant", 5);
            }
            processLine.push_back(newSockFileDesc);
            // lock.release();
        }

        // Release access
        found = access.find("release");
        if (found != std::string::npos)
        {
            // lock.acquire(); // Dont know if it need lock here
            processLine.erase(processLine.begin());
            if (processLine.size() > 0)
            {
                response = write(processLine[0], "grant", 5);
            }
            // lock.release(); // Dont know if it need lock here
        }

        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }

        bzero(buffer, BUFFER_SIZE);
    }

    close(newSockFileDesc);
}

void *connect (void *arguments)
{
    struct arg_struct *args = (struct arg_struct *) arguments;

    listen(*args->sockFileDesc, MAX_CONNECTIONS);
    socklen_t clientLen = sizeof(args->clientAddr);
    while (true)
    {
        int newSockFileDesc = accept(*args->sockFileDesc, (struct sockaddr *) &args->clientAddr, &clientLen);
        if(newSockFileDesc < 0)
        {
            error((char *) "ERROR accepting client connection");
        }

         /* Create child process */
        int pid = fork();
          
        if (pid < 0) 
        {
           perror("ERROR on fork");
           exit(1);
        }
        
        if (pid == 0) 
        {
           /* This is the client process */
           // close(sockfd);
           doTheJob(newSockFileDesc);
           // exit(0);
        }
        else 
        {
           close(newSockFileDesc);
        }
    }
}


int main(int argc, const char* argv[])
{
	// get RTC (real time clock)
	using std::chrono::system_clock;
	system_clock::time_point today = system_clock::now(); 

	std::time_t tt;
  	tt = system_clock::to_time_t(today);
  	std::cout << "today is: " << std::ctime(&tt) << std::endl;

  	// Log file
  	std::string fileName = "log.txt";

  	// Creating server
    int sockFileDesc, newSockFileDesc, response, indexOfZero;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;

    sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);

    if(sockFileDesc < 0)
    {
        error((char *) "ERROR opening socket");
    }

    // bzero() sets all values in a buffer to zero
    bzero((char *) &serverAddr, sizeof(serverAddr));

    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(PORT_NO);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // bind() binds a socket to an address
    if(bind(sockFileDesc, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        error((char *) "ERROR binding socket");
    }

    // Thread to accept new connections
    pthread_t acceptConnections;
    struct arg_struct pArgs;
    pArgs.sockFileDesc = &sockFileDesc;
    pArgs.clientAddr   = (struct sockaddr_in *) &clientAddr;
    pthread_create(&acceptConnections, NULL, connect, (void *) &pArgs);
    pthread_join(acceptConnections, NULL);
	
	// Writing to a file
	// ofstream myfile;
	// writeToFile(myfile, "oie", "log.txt");
	return 0;
}