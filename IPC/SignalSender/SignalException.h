//
// Created by Eric Reis on 4/18/16.
//

#ifndef SIGNALSENDER_SIGNALEXCEPTION_H
#define SIGNALSENDER_SIGNALEXCEPTION_H

#include <stdexcept>
#include <string>


class SignalException : public std::runtime_error
{
public:
    SignalException(const std::string &message)
            : std::runtime_error(message)
    { }
};

#endif //SIGNALSENDER_SIGNALEXCEPTION_H
