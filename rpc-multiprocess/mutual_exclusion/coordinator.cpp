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
#include <signal.h>

#include "lock.hpp"

#define BUFFER_SIZE 256
#define PORT_NO 12345
#define MAX_CONNECTIONS 1000

// g++ coordinator.cpp -o coordinator.out -std=c++11

using std::chrono::system_clock;

std::chrono::high_resolution_clock::time_point startTime;
std::chrono::high_resolution_clock::time_point endTime;

std::vector<int> processLine;
Lock lock;
Lock clientsLock; // Just checking client connections (in order to get total execution time)
std::ofstream myfile;
std::string fileName = "log.txt";
std::time_t tt;

int numberOfClients = 128;

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
        std::string access(buffer);
        bzero(buffer, BUFFER_SIZE);

        // Requesting access
        std::size_t found = access.find("request");
        if (found != std::string::npos)
        {
            lock.acquire();
            system_clock::time_point today = system_clock::now();
            tt = system_clock::to_time_t(today);
            std::string str(std::ctime(&tt));
            std::string msg = "Received request message. RTC: " + str;
            writeToFile(myfile, msg, fileName);
            if (processLine.size() == 0)
            {
                // Queue is empty
                system_clock::time_point today = system_clock::now();
                tt = system_clock::to_time_t(today);
                std::string str(std::ctime(&tt));
                std::string msg = "Sending grant message to this process. RTC: " + str;
                writeToFile(myfile, msg, fileName);
                response = write(newSockFileDesc, "grant", 5);
            }
            processLine.push_back(newSockFileDesc);
            lock.release();
        }

        // Release access
        found = access.find("release");
        if (found != std::string::npos)
        {
            lock.acquire(); // Dont know if it need lock here
            system_clock::time_point today = system_clock::now();
            tt = system_clock::to_time_t(today);
            std::string str(std::ctime(&tt));
            std::string msg = "Received release message. RTC: " + str;
            writeToFile(myfile, msg, fileName);
            processLine.erase(processLine.begin());
            if (processLine.size() > 0)
            {
                system_clock::time_point today = system_clock::now();
                tt = system_clock::to_time_t(today);
                std::string str(std::ctime(&tt));
                std::string msg = "Sending grant message to other process. RTC: " + str;
                writeToFile(myfile, msg, fileName);
                response = write(processLine[0], "grant", 5);
            }
            lock.release(); // Dont know if it need lock here
        }

        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }

        bzero(buffer, BUFFER_SIZE);
    }
}

void *connect (void *arguments)
{
    struct arg_struct *args = (struct arg_struct *) arguments;

    listen(*args->sockFileDesc, MAX_CONNECTIONS);
    socklen_t clientLen = sizeof(args->clientAddr);
    int connections = 0;
    
    while (true)
    {
        int newSockFileDesc = accept(*args->sockFileDesc, (struct sockaddr *) &args->clientAddr, &clientLen);
        if(newSockFileDesc < 0)
        {
            error((char *) "ERROR accepting client connection");
        }

        clientsLock.acquire();
        connections++;
        std::cout << connections << std::endl;
        if (connections == 1)
        {
            startTime = std::chrono::high_resolution_clock::now();
        }
        clientsLock.release();

         /* Create child process */
        int pid = fork();
          
        if (pid < 0) 
        {
           perror("ERROR on fork");
           exit(1);
        }
        
        if (pid == 0) 
        {
            doTheJob(newSockFileDesc);
            // Closing connection
            clientsLock.acquire();
            if (connections == numberOfClients)
            {
                endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> endTimeSpan = std::chrono::duration_cast< std::chrono::duration<double> >(endTime - startTime);
                std::cout << "end: " << endTimeSpan.count() << " secs" << std::endl;
            }
            clientsLock.release();
            close(newSockFileDesc);
            exit(0);
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
	system_clock::time_point today = system_clock::now();

  	tt = system_clock::to_time_t(today);
  	std::cout << "today is: " << std::ctime(&tt) << std::endl;

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
	
	return 0;
}