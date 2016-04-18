#include <iostream>

#include "SignalSender.h"
#include "SignalException.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Wrong parameters" << std::endl;
    }

    int ret;

    int signum = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);

    try
    {
        SignalSender sender;

        // check whether the desired process exists or not
        if (sender.processExists(pid))
        {
            int status = sender.sendSignal(signum, pid);

            if (status == 0)
            {
                std::cout << "Sent signal " << signum << " to process " << pid << std::endl;
            }
            if (status == -1)
            {
                throw SignalException("Error sending signal");
            }
        }
        else
        {
            throw SignalException("Process does not exists");
        }

        ret = EXIT_SUCCESS;
    }
    catch (SignalException &e)
    {
        std::cerr << "SignalException: " << e.what() << std::endl;
        ret = EXIT_FAILURE;
    }

    return ret;
}