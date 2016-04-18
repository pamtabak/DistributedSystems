#include <iostream>

#include "SignalHandler.h"

int main(int argc, const char* argv[])
{
    int ret;

    try
    {
        SignalHandler handler;

        handler.setupSignalHandlers();

        while(!handler.terminate(handler.getSignum()))
        {
            std::cout << "Waiting for signal ..." << std::endl;
            if(argc > 1 && strcmp(argv[1], "blocking") == 0)
            {
                sleep(2);
            }
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