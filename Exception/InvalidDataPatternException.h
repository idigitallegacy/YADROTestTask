//
// Created by elfxe on 07.06.2023.
//

#ifndef TESTTASK_INVALIDPATTERNEXCEPTION_CPP
#define TESTTASK_INVALIDPATTERNEXCEPTION_CPP
#include <exception>
#include "../cfg.h"

class InvalidDataPatternException : public std::exception {
private:
    INDEX_T _lineNumber;
    INDEX_T _columnNumber;
    std::string _value;
    const char *_message;
public:
    explicit InvalidDataPatternException(INDEX_T lineNumber = 0, INDEX_T columnNumber = 0, std::string value = "", const char *message = "") : _value(std::move(value)), _message(message), _lineNumber(lineNumber), _columnNumber(columnNumber) { }

    [[nodiscard]] INDEX_T lineNumber() const {
        return _lineNumber;
    }

    [[nodiscard]] INDEX_T columnNumber() const {
        return _columnNumber;
    }

    std::string value() {
        return _value;
    }

    const char * what() {
        return _message;
    }
};

#endif