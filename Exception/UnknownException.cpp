//
// Created by elfxe on 13.06.2023.
//

#ifndef TESTTASK_UNKNOWNEXCEPTION_CPP
#define TESTTASK_UNKNOWNEXCEPTION_CPP

#include <exception>
#include <string>
#include "../cfg.h"

class UnknownException : public std::exception {
private:
    std::string _debugData;
    const char *_message;
public:
    explicit UnknownException(std::string debugData = "", const char *message = "") : _debugData(std::move(debugData)), _message(message) { }

    std::string debugData() {
        return _debugData;
    }

    const char * what() {
        return _message;
    }
};

#endif //TESTTASK_UNKNOWNEXCEPTION_CPP
