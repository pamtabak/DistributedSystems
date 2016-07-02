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

#define BUFFER_SIZE 256
#define PORT_NO 666
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
  	int response;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr;
    struct hostent *server;

    int sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);
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

    while(true)
    {
        bzero(buffer, BUFFER_SIZE);
        response = read(sockFileDesc, buffer, BUFFER_SIZE - 1); // request from client 
        if(response < 0)
        {
            error((char *) "ERROR reading from socket");
        }

        int n = atoi(buffer);
        if(n == 0)
        {
            break;
        }

        std::string s = accessType[0];
        const char *c = s.c_str();
        response = write(sockFileDesc, c, s.size()); // answering client with one of the options
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }
    }
    close(sockFileDesc);
	

	// Writing to a file
	// ofstream myfile;
	// writeToFile(myfile, "oie", "log.txt");
	return 0;
}