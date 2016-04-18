//
// Created by Eric Reis on 4/18/16.
//

#ifndef SIGNALSENDER_SIGNALSENDER_H
#define SIGNALSENDER_SIGNALSENDER_H


#include <sys/types.h>
#include <signal.h>

class SignalSender
{
public:
    SignalSender();
    ~SignalSender();

    bool processExists(pid_t pid);

    int sendSignal(int signum);
    int sendSignal(int signum, pid_t pid);
};


#endif //SIGNALSENDER_SIGNALSENDER_H
