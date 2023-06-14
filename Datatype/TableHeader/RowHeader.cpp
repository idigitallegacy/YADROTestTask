//
// Created by elfxe on 07.06.2023.
//

#include <string>
#include "Header.cpp"
#include "../../cfg.h"

#ifndef TESTTASK_ROWHEADER
#define TESTTASK_ROWHEADER

class RowHeader : public Header {
private:
    static bool stringValidator(const std::string &string) {
        std::regex regexMatcher("^[0-9]+$");
        return std::regex_match(string, regexMatcher);
    }

public:
    RowHeader() : Header() { }

    RowHeader(INDEX_T indexValue, const std::string &stringValue) : Header(indexValue, stringValue) {
        if (!stringValidator(stringValue))
            throw InvalidDataPatternException(indexValue, 0, stringValue, "Invalid row header value met.");
    }

    RowHeader(const RowHeader &cpd) : Header(cpd._indexValue, cpd._stringValue) {}
};


#endif //TESTTASK_ROWHEADER
