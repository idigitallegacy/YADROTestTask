//
// Created by elfxe on 13.06.2023.
//

#ifndef TESTTASK_INVALIDCELLTREEEXCEPTION_CPP
#define TESTTASK_INVALIDCELLTREEEXCEPTION_CPP

#include "UnknownException.cpp"

class InvalidCellTreeException : public UnknownException {
private:
    INDEX_T _lineNumber;
    INDEX_T _columnNumber;
    std::string _value;
public:
    explicit InvalidCellTreeException(
            INDEX_T lineNumber = 0,
            INDEX_T columnNumber = 0,
            std::string value = "",
            const char *message = "")
            : _value(std::move(value)),
            _lineNumber(lineNumber),
            _columnNumber(columnNumber),
            UnknownException("", message) { }

    [[nodiscard]] INDEX_T lineNumber() const {
        return _lineNumber;
    }

    [[nodiscard]] INDEX_T columnNumber() const {
        return _columnNumber;
    }

    std::string cellValue() {
        return _value;
    }
};

#endif //TESTTASK_INVALIDCELLTREEEXCEPTION_CPP
