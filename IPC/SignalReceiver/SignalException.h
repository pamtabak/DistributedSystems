//
// Created by Eric Reis on 4/17/16.
//

#ifndef SIGNALS_SIGNALEXCEPTION_H
#define SIGNALS_SIGNALEXCEPTION_H

#include <stdexcept>
#include <string>


class SignalException : public std::runtime_error
{
public:
    SignalException(const std::string &message)
            : std::runtime_error(message)
    { }
};


#endif //SIGNALS_SIGNALEXCEPTION_H
