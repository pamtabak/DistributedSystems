//
// Created by Eric Reis on 4/17/16.
//

#include "SignalHandler.h"

bool SignalHandler::gotExitSignal = false;

/**
 * Default Constructor
 */
SignalHandler::SignalHandler()
{

}

/**
 * Default Destructor
 */
SignalHandler::~SignalHandler()
{

}

/**
 * Return the bool flag indicating whether the program received an exit signal
 * @return Flag indicating shutdown of program
 */
bool SignalHandler::getGotExitSignal()
{
    return SignalHandler::gotExitSignal;
}

/**
 * Sets the bool flag indicating whether the program received an exit signal
 */
void SignalHandler::setGotExitSignal(bool gotExitSignal)
{
    SignalHandler::gotExitSignal = gotExitSignal;
}

/**
 * Sets exit signal to true
 * @param[in] exit Not used but required by function prototype to match required handler
 */
void SignalHandler::exitSignalHandler(int exit)
{
    SignalHandler::gotExitSignal = true;
}

/**
 * Set up the signal handlers for the following
 * CTRL-C, ... (not implemented yet)
 */
void SignalHandler::setupSignalHandlers()
{
    if(signal((int) SIGINT, SignalHandler::exitSignalHandler) == SIG_ERR)
    {
        throw SignalException("Error setting up handlers ...");
    }
}

