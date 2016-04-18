//
// Created by Eric Reis on 4/18/16.
//

#include "SignalSender.h"

/**
 * Default Constructor
 */
SignalSender::SignalSender()
{

}

/**
 * Destructor
 */
SignalSender::~SignalSender()
{

}

/**
 * Returns the bool flag indicating whether the desired process exists
 * @param[in] pid
 * @return bool flag indicating process existence
 */
bool SignalSender::processExists(pid_t pid)
{
    return 0 == kill(pid, 0);
}

/**
 * Sends a signal to the current executing program
 * @param[in] signum
 * @return int value which represents the status of the signal
 */
int SignalSender::sendSignal(int signum)
{
    return raise(signum);
}

/**
 * Sends a signal to the specified process
 * @param[in] signum, pid
 * @return int value which represents the status of the signal
 */
int SignalSender::sendSignal(int signum, pid_t pid)
{
    return kill(pid, signum);
}
