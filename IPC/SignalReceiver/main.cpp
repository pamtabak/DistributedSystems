#include <iostream>

#include "SignalHandler.h"

int main()
{
    int ret;

    try
    {
        SignalHandler handler;

        handler.setupSignalHandlers();

        while(handler.getSignum() != SIGINT)
        {
            std::cout << "Waiting for signal ..." << std::endl;
            sleep(1);
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