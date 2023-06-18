//
// Created by elfxe on 07.06.2023.
//

#ifndef TESTTASK_HEADER
#define TESTTASK_HEADER

#include <string>
#include <regex>
#include "../../cfg.h"
#include "../../Exception/InvalidDataPatternException.cpp"

class Header {
protected:
    std::string _stringValue;
    INDEX_T _indexValue;

    Header() {
        _indexValue = 0;
        _stringValue = "";
    }

    Header(INDEX_T indexValue, const std::string &stringValue) {
        _stringValue = stringValue;
        _indexValue = indexValue;
    }

public:

    [[nodiscard]] virtual std::string getStringValue() const {
        return _stringValue;
    }

    [[nodiscard]] virtual INDEX_T getIndexValue() const {
        return _indexValue;
    }
};


#endif //TESTTASK_HEADER