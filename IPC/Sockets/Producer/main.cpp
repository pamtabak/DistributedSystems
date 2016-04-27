#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

#define RAND(min, max) rand() % (max - min + 1) + min

#define BUFFER_SIZE 256
#define PORT_NO 666
#define MAX_CONNECTIONS 5

/**
 * Returns a random number larger than the last ont generated and between the min/max value
 * @param[in] lastRandomNumber, min, max
 * @return int random number
 */
int getIncreasingRandomNumber(int min, int max)
{
    srand(time(NULL));
    return RAND(min, max);;
}

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockFileDesc, newSockFileDesc, response, indexOfZero;
    socklen_t clientLen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;

    if(argc != 2)
    {
        std::cout << "Wrong parameters." << std::endl;
        return EXIT_FAILURE;
    }

    sockFileDesc = socket(AF_INET, SOCK_STREAM, 0);

    if(sockFileDesc < 0)
    {
        error((char *) "ERROR opening socket");
    }

    // bzero() sets all values in a buffer to zero
    bzero((char *) &serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NO);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // bind() binds a socket to an address
    if(bind(sockFileDesc, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        error((char *) "ERROR binding socket");
    }

    // listen() allows the process to listen on the socket for connections. The second argument is the
    // number of connections that can be waiting while the process is handling a particular connection
    listen(sockFileDesc, MAX_CONNECTIONS);

    clientLen = sizeof(clientAddr);
    // accept() causes the process to block until a client connects to the server
    newSockFileDesc = accept(sockFileDesc, (struct sockaddr *) &clientAddr, &clientLen);
    if(newSockFileDesc < 0)
    {
        error((char *) "ERROR accepting client connection");
    }

    indexOfZero = atoi(argv[1]);
    int delta, min, max, randomNumber;
    delta = std::numeric_limits<int>::max() / indexOfZero;
    min = 0;
    max = delta;
    for(int i = 0; i < indexOfZero; i++)
    {
        randomNumber = getIncreasingRandomNumber(min, max);
        min += delta;
        max += delta;
        std::string s = std::to_string(randomNumber);
        const char * c = s.c_str();
        response = write(newSockFileDesc, c, s.size());
        if(response < 0)
        {
            error((char *) "ERROR writing to socket");
        }

        bzero(buffer, BUFFER_SIZE);
        // read() blocks until there is something for it to read in the socket
        response = read(newSockFileDesc, buffer, BUFFER_SIZE - 1);
        if(response < 0)
        {
            error((char *) "ERROR reading from socket");
        }
        std::cout << "The number " << s << " is prime: " << buffer << std::endl;
    }
    response = write(newSockFileDesc, "0", 1);
    if(response < 0)
    {
        error((char *) "ERROR writing to socket");
    }

    close(newSockFileDesc);
    close(sockFileDesc);


    return 0;
}