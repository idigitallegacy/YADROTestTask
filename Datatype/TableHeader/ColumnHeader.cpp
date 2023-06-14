//
// Created by elfxe on 07.06.2023.
//
#include <string>
#include <regex>
#include "Header.cpp"

#ifndef TESTTASK_COLUMNHEADER_H
#define TESTTASK_COLUMNHEADER_H

class ColumnHeader : public Header {
private:
    static bool stringValidator(const std::string &string) {
        std::regex regexMatcher("^[a-zA-Z]+$");
        return std::regex_match(string, regexMatcher);
    }

public:
    ColumnHeader() : Header() { }

    ColumnHeader(INDEX_T indexValue, const std::string &stringValue) : Header(indexValue, stringValue) {
        if (!stringValidator(stringValue))
            throw InvalidDataPatternException(0, indexValue, stringValue, "Invalid column header value met.");
    }

    ColumnHeader(const ColumnHeader &cpd) : Header(cpd._indexValue, cpd._stringValue) {}
};

#endif //TESTTASK_COLUMNHEADER_H
