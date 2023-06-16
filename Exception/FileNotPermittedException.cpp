//
// Created by elfxe on 13.06.2023.
//

#ifndef TESTTASK_FILENOTPERMITTEDEXCEPTION_CPP
#define TESTTASK_FILENOTPERMITTEDEXCEPTION_CPP

#include <exception>

class FileNotPermittedException : public std::exception {
private:
    const char *_message;
public:
    explicit FileNotPermittedException(const char *message = "") : _message(message) { }

    const char * what() {
        return _message;
    }
};
#endif //TESTTASK_FILENOTPERMITTEDEXCEPTION_CPP
