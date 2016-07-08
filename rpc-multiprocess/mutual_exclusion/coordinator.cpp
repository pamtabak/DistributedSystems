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

// using namespace std;

// g++ main.cpp -o main.out -std=c++11

// Uma thread para aceitar novas conexoes. Cada nova conexao sera uma thread tambem. Usar lock para ver a fila de processos

std::vector<int> processLine;

struct arg_struct
{
    int *sockFileDesc;
    struct sockaddr_in * clientAddr;

};

struct client_struct
{
    int *newSockFileDesc;
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

void *doTheJob (void *arguments)
{
    struct client_struct *args = (struct client_struct *) arguments;
    char buffer[BUFFER_SIZE];
    int response;
    int newSockFileDesc = *args->newSockFileDesc;

    while (true)
    {
        // clientLen = sizeof(clientAddr);
        // newSockFileDesc = accept(sockFileDesc, (struct sockaddr *) &clientAddr, &clientLen);
        // if(newSockFileDesc < 0)
        // {
        //     error((char *) "ERROR accepting client connection");
        // }
        
        bzero(buffer, BUFFER_SIZE);
        
        // read() blocks until there is something for it to read in the socket
        response = read(newSockFileDesc, buffer, BUFFER_SIZE - 1); // request to write on file
        if(response < 0)
        {
            error((char *) "ERROR reading from socket");
        }
        else if (response == 0)
        {
            // client has closed its connection
            break;
        }

        std::string access(buffer);
        bzero(buffer, BUFFER_SIZE);

        // Requesting access
        std::size_t found = access.find("request");
        if (found != std::string::npos)
        {
            if (processLine.size() == 0)
            {
                // Queue is empty
                response = write(newSockFileDesc, "grant", 5);
            }

            processLine.push_back(newSockFileDesc);
        }

        // Release access
        found = access.find("release");
        if (found != std::string::npos)
        {
            processLine.erase(processLine.begin());
            if (processLine.size() > 0)
            {
                response = write(processLine[0], "grant", 5);
            }
        }

        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }
    }

    close(newSockFileDesc);
    // close(sockFileDesc);
}

void *connect (void *arguments)
{
    struct arg_struct *args = (struct arg_struct *) arguments;

    while (true)
    {
        listen(*args->sockFileDesc, MAX_CONNECTIONS);
        socklen_t clientLen = sizeof(args->clientAddr);
        int newSockFileDesc = accept(*args->sockFileDesc, (struct sockaddr *) &args->clientAddr, &clientLen);
        if(newSockFileDesc < 0)
        {
            error((char *) "ERROR accepting client connection");
        }

        // Create Thread to work with this specific client
        pthread_t client;
        struct client_struct cArgs;
        cArgs.newSockFileDesc = &newSockFileDesc;
        pthread_create(&client, NULL, doTheJob, (void *) &cArgs);
        pthread_join(client, NULL);
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
  	// std::string accessType[3] = { "request", "grant", "release"};

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

    // listen(sockFileDesc, MAX_CONNECTIONS);

    // socklen_t  clientLen = sizeof(clientAddr);
    // newSockFileDesc = accept(sockFileDesc, (struct sockaddr *) &clientAddr, &clientLen);
    // if(newSockFileDesc < 0)
    // {
    //     error((char *) "ERROR accepting client connection");
    // }

    // Thread to accept new connections
    pthread_t acceptConnections;
    struct arg_struct pArgs;
    pArgs.sockFileDesc = &sockFileDesc;
    pArgs.clientAddr   = (struct sockaddr_in *) &clientAddr;
    pthread_create(&acceptConnections, NULL, connect, (void *) &pArgs);
    pthread_join(acceptConnections, NULL);

    // while (true)
    // {
    //     // clientLen = sizeof(clientAddr);
    //     // newSockFileDesc = accept(sockFileDesc, (struct sockaddr *) &clientAddr, &clientLen);
    //     // if(newSockFileDesc < 0)
    //     // {
    //     //     error((char *) "ERROR accepting client connection");
    //     // }
        
    //     bzero(buffer, BUFFER_SIZE);
        
    //     // read() blocks until there is something for it to read in the socket
    //     response = read(newSockFileDesc, buffer, BUFFER_SIZE - 1); // request to write on file
    //     if(response < 0)
    //     {
    //         error((char *) "ERROR reading from socket");
    //     }
    //     else if (response == 0)
    //     {
    //         // client has closed its connection
    //         continue;
    //     }

    //     std::string access(buffer);
    //     bzero(buffer, BUFFER_SIZE);

    //     // Requesting access
    //     std::size_t found = access.find("request");
    //     if (found != std::string::npos)
    //     {
    //         if (processLine.size() == 0)
    //         {
    //             // Queue is empty
    //             response = write(newSockFileDesc, "grant", 5);
    //         }

    //         processLine.push_back(newSockFileDesc);
    //     }

    //     // Release access
    //     found = access.find("release");
    //     if (found != std::string::npos)
    //     {
    //         processLine.erase(processLine.begin());
    //         if (processLine.size() > 0)
    //         {
    //             response = write(processLine[0], "grant", 5);
    //         }
    //     }

    //     if(response < 0)
    //     {
    //         error((char *) "ERROR writing to socket");
    //     }
    // }

    // close(newSockFileDesc);
    // close(sockFileDesc);
	
	// Writing to a file
	// ofstream myfile;
	// writeToFile(myfile, "oie", "log.txt");
	return 0;
}