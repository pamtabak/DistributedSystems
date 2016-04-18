//
// Created by Eric Reis on 4/17/16.
//

#ifndef SIGNALS_SIGNALHANDLER_H
#define SIGNALS_SIGNALHANDLER_H

#include <signal.h>
#include <errno.h>

#include "SignalException.h"


class SignalHandler
{
protected:
    static bool gotExitSignal;

public:
    SignalHandler();
    ~SignalHandler();

    static bool getGotExitSignal();
    static void setGotExitSignal(bool gotExitSignal);

    void setupSignalHandlers();
    static void exitSignalHandler(int exit);
};


#endif //SIGNALS_SIGNALHANDLER_H
