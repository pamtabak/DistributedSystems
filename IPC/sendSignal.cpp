#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

// signal getSignal (string signalType){
// 	signal signalChosen;

// 	switch (signalType){
// 		case "SIGABRT":
// 			signalChosen = SIGABRT;
// 			break;

// 		case default:
// 			signalChosen = SIGABRT;
// 			break;
// 	}

// 	return signalChosen;
// }

int main(int argc, char * argv[])
{
	// Interation with user
	std::string pid;
	std::cout << "Digite o numero do processo de destino." << std::endl;
	std::cin >> pid;

	std::string signalString;
	std::cout << "Digite o sinal que deve ser enviado" << std::endl;
	std::cin >> signalString;

	// signal signum = getSignal(signalString);

	if (0 == kill(pid, 0))
	{
    	// Process exists.

		raise(int sig); // returns int. Generates a signal

		int status = kill(pid, signum);

		if (status == 0)
		{
			// everything went ok
		}
		if (status == -1)
		{
			// error! Signal not sent
		}
	}
	else
	{
		// Process doesnt exist
		// show some error
		return -1;
	}

	return 0;
}