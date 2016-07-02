#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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

#define BUFFER_SIZE 256
#define PORT_NO 12345
#define MAX_CONNECTIONS 5

// using namespace std;

// g++ main.cpp -o main.out -std=c++11

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
  	std::string accessType[3] = { "request", "grant", "release"};


  	// Creating server
    int sockFileDesc, newSockFileDesc, response, indexOfZero;
    socklen_t clientLen;
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

    listen(sockFileDesc, MAX_CONNECTIONS);

    while (true)
    {
        clientLen = sizeof(clientAddr);
        newSockFileDesc = accept(sockFileDesc, (struct sockaddr *) &clientAddr, &clientLen);
        if(newSockFileDesc < 0)
        {
            error((char *) "ERROR accepting client connection");
        }

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
            continue;
        }

        std::cout << response << std::endl;

        // verifica se ja tem algum processo escrevendo no arquivo e responde o cliente
        response = write(newSockFileDesc, "OK", 2);
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }
    }

    close(newSockFileDesc);
    close(sockFileDesc);
	
	// Writing to a file
	// ofstream myfile;
	// writeToFile(myfile, "oie", "log.txt");
	return 0;
}