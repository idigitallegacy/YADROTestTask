//
// Created by elfxe on 13.06.2023.
//

#ifndef TESTTASK_EMPTYDATAEXCEPTION_H
#define TESTTASK_EMPTYDATAEXCEPTION_H

#include <exception>
#include <utility>
#include "../cfg.h"

class EmptyDataException : public std::exception {
private:
    INDEX_T _lineNumber;
    INDEX_T _columnNumber;
    std::string _line;
    const char *_message;
public:
    explicit EmptyDataException(INDEX_T lineNumber = 0, INDEX_T columnNumber = 0, std::string line = "", const char *message = "") : _line(std::move(line)), _message(message), _lineNumber(lineNumber), _columnNumber(columnNumber) { }

    [[nodiscard]] INDEX_T lineNumber() const {
        return _lineNumber;
    }

    [[nodiscard]] INDEX_T columnNumber() const {
        return _columnNumber;
    }

    std::string line() {
        return _line;
    }

    const char * what() {
        return _message;
    }
};

#endif //TESTTASK_EMPTYDATAEXCEPTION_H
