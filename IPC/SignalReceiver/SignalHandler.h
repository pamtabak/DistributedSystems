//
// Created by Eric Reis on 4/17/16.
//

#ifndef SIGNALS_SIGNALHANDLER_H
#define SIGNALS_SIGNALHANDLER_H

#include <iostream>
#include <signal.h>
#include <errno.h>

#include "SignalException.h"


class SignalHandler
{
protected:
    static int signum;
    static int signals[29];

public:
    SignalHandler();
    ~SignalHandler();

    static int getSignum();
    static void setSignum(bool gotExitSignal);

    void setupSignalHandlers();
    static void signalHandlers(int signum);
};


#endif //SIGNALS_SIGNALHANDLER_H
