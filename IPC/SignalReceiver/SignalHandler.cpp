//
// Created by Eric Reis on 4/17/16.
//

#include "SignalHandler.h"

int SignalHandler::signum = 0;
int SignalHandler::signals[29] =
        {
            SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT,
            SIGEMT, SIGFPE, SIGBUS, SIGSEGV, SIGSYS, SIGPIPE,
            SIGALRM, SIGTERM, SIGURG, SIGTSTP, SIGCONT, SIGCHLD,
            SIGTTIN, SIGTTOU, SIGIO, SIGXCPU, SIGXFSZ, SIGVTALRM,
            SIGPROF, SIGWINCH, SIGINFO, SIGUSR1, SIGUSR2
        };

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
 * Return the int indicating which signal the program received
 * @return int indicating received signal
 */
int SignalHandler::getSignum()
{
    return SignalHandler::signum;
}

/**
 * Sets the int indicating which signal the program received
 */
void SignalHandler::setSignum(bool signum)
{
    SignalHandler::signum = signum;
}

/**
 * Handle each possible signal when received
 * @param[in] signum
 */
void SignalHandler::signalHandlers(int signum)
{
    SignalHandler::signum = signum;

    switch(SignalHandler::signum)
    {
        case SIGHUP:
            std::cout << "Caught Hangup Signal" << std::endl;
            break;
        case SIGINT:
            std::cout << "Caught Interrupt signal" << std::endl;
            break;
        case SIGQUIT:
            std::cout << "Caught Quit Signal" << std::endl;
            break;
        case SIGILL:
            std::cout << "Caught Illegal Instruction Signal" << std::endl;
            break;
        case SIGTRAP:
            std::cout << "Caught Trace trap Signal" << std::endl;
            break;
        case SIGABRT:
            std::cout << "Caught Abort Signal" << std::endl;
            break;
        case SIGEMT:
            std::cout << "Caught Emulator Trap Signal" << std::endl;
            break;
        case SIGFPE:
            std::cout << "Caught Floating Point Exception Signal" << std::endl;
            break;
        case SIGBUS:
            std::cout << "Caught BUS Error Signal" << std::endl;
            break;
        case SIGSEGV:
            std::cout << "Caught Segmentation Violation Signal" << std::endl;
            break;
        case SIGSYS:
            std::cout << "Caught Bad System Call Signal" << std::endl;
            break;
        case SIGPIPE:
            std::cout << "Caught Broken Pipe Signal" << std::endl;
            break;
        case SIGALRM:
            std::cout << "Caught Alarm Clock Signal" << std::endl;
            break;
        case SIGTERM:
            std::cout << "Caught Termination Signal" << std::endl;
            break;
        case SIGURG:
            std::cout << "Caught Urgent Condition On Socket Signal" << std::endl;
            break;
        case SIGTSTP:
            std::cout << "Caught Keyboard Stop Signal" << std::endl;
            break;
        case SIGCONT:
            std::cout << "Caught Continue Signal" << std::endl;
            break;
        case SIGCHLD:
            std::cout << "Caught Child Status Has Changed Signal" << std::endl;
            break;
        case SIGTTIN:
            std::cout << "Caught Background Read From TTY Signal" << std::endl;
            break;
        case SIGTTOU:
            std::cout << "Caught Background Write To TTY Signal" << std::endl;
            break;
        case SIGIO:
            std::cout << "Caught I/O Now Possible Signal" << std::endl;
            break;
        case SIGXCPU:
            std::cout << "Caught CPU Limit Exceeded Signal" << std::endl;
            break;
        case SIGXFSZ:
            std::cout << "Caught Hangup Signal" << std::endl;
            break;
        case SIGVTALRM:
            std::cout << "Caught Virtual Time Alarm Signal" << std::endl;
            break;
        case SIGPROF:
            std::cout << "Caught Profiling Alarm Clock Signal" << std::endl;
            break;
        case SIGWINCH:
            std::cout << "Caught Window Size Changed Signal" << std::endl;
            break;
        case SIGINFO:
            std::cout << "Caught Status Request Received From Controlling Terminal Signal" << std::endl;
            break;
        case SIGUSR1:
            std::cout << "Caught User-defined Signal 1" << std::endl;
            break;
        case SIGUSR2:
            std::cout << "Caught User-defined Signal 2" << std::endl;
            break;
        default:
            std::cout << "Caught Default Signal" << std::endl;
            break;
    }
}

/**
 * Set up the signal handlers for all available signals
 * Signal SIGKILL and SIGSTOP cannot be handled
 */
void SignalHandler::setupSignalHandlers()
{
    for(int i = 0; i < 29; i++)
    {
        if(signal((int) SignalHandler::signals[i], SignalHandler::signalHandlers) == SIG_ERR)
        {

            throw SignalException("Error setting up handlers ...");
        }
    }
}

/**
 * Checks whether the received signal terminates de process
 * @param[in] signum
 * @return bool flag indicating whether the process should be terminated
 */
bool SignalHandler::terminate(int signum)
{
    if(signum == SIGHUP || signum == SIGINT || signum == SIGQUIT || signum == SIGKILL || signum == SIGTERM)
    {
        return true;
    }
    return false;
}
