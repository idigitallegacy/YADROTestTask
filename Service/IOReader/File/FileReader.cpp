//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_FILEREADER_CPP
#define TESTTASK_FILEREADER_CPP

#include <vector>
#include <string>
#include <fstream>
#include "../../../Exception/FileNotPermittedException.cpp"

class FileReader {
private:
    std::vector<std::string> _fileAsStringArray;

    void read(std::ifstream &fileStream) {
        if (!fileStream.is_open()) {
            throw FileNotPermittedException("File can not be opened in read mode.");
        }

        std::string tempString;
        while (fileStream >> tempString)
            _fileAsStringArray.push_back(tempString);
    }

public:
    FileReader() = default;

    explicit FileReader(std::ifstream &fileStream) {
        _fileAsStringArray = std::vector<std::string>();
        read(fileStream);
    }

    [[nodiscard]] std::vector<std::string> getLines() const {
        return _fileAsStringArray;
    }
};


#endif //TESTTASK_FILEREADER_CPP
