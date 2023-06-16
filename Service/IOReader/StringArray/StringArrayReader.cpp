//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_STRINGARRAYREADER_CPP
#define TESTTASK_STRINGARRAYREADER_CPP

#include <vector>
#include <string>
#include <exception>

#include "../../../Datatype/TableHeader/ColumnHeader.cpp"
#include "../../../Datatype/TableHeader/RowHeader.cpp"
#include "../File/FileReader.cpp"
#include "../../../cfg.h"

#include "../../../Exception/EmptyDataException.cpp"

class StringArrayReader {
private:
    std::vector<std::string> _fileAsStringArray;
    std::vector<ColumnHeader> _columnHeaders;
    std::vector<RowHeader> _rowHeaders;
    std::vector<std::vector<std::string>> _tableCells;

    INDEX_T _verticalSize = 0;
    INDEX_T _horizontalSize = 0;

    void parseColumnHeaders() {
        if (_fileAsStringArray.empty())
            return;
        std::stringstream ss(_fileAsStringArray[0]);
        INDEX_T index = 0;
        std::string headerName;
        while (ss.good()) {
            std::getline( ss, headerName, ',' );
            if (index == 0 && headerName.empty())
                continue;
            else if (headerName.empty())
                throw EmptyDataException(0, index, _fileAsStringArray[0], "Empty column header met.");
            ColumnHeader header = ColumnHeader(index, headerName);
            _columnHeaders.push_back(header);
            ++index;
            ++_horizontalSize;
        }
    }

    void parseRowHeaders() {
        if (_fileAsStringArray.empty())
            return;
        std::stringstream ss;
        INDEX_T index = 0;

        // Building a string of row headers split by ','
        for (auto &i : _fileAsStringArray) {
            ss << ',';
            std::stringstream tempSs(i);
            std::string tempString;
            std::getline(tempSs, tempString, ',');
            ss << tempString;
        }

        // Parsing built string as it done with column headers
        std::string headerName;
        while (ss.good()) {
            std::getline( ss, headerName, ',' );
            if (index == 0 && headerName.empty())
                continue;
            else if (headerName.empty())
                throw EmptyDataException(index, 0, _fileAsStringArray[index], "Empty column header met.");
            RowHeader header = RowHeader(index, headerName);
            _rowHeaders.push_back(header);
            ++index;
            ++_verticalSize;
        }
    }

    void parseTableCells() {
        if (_fileAsStringArray.empty())
            return;

        INDEX_T verticalIndex = -1;
        for (auto &i : _fileAsStringArray) {
            _tableCells.emplace_back();

            // skipping the column header line
            if (verticalIndex == -1) {
                ++verticalIndex;
                continue;
            }

            std::stringstream lineSs(i);
            std::string columnString;

            INDEX_T horizontalIndex = -1;
            while (lineSs.good()) {
                // skipping the row header column
                if (horizontalIndex == -1) {
                    std::getline(lineSs, columnString, ',');
                    ++horizontalIndex;
                    continue;
                }

                std::getline( lineSs, columnString, ',' );
                if (columnString.empty())
                    throw EmptyDataException(verticalIndex + 1, horizontalIndex, _fileAsStringArray[verticalIndex + 1], "Empty data met.");
                _tableCells[verticalIndex].push_back(columnString);
                ++horizontalIndex;
            }

            if (horizontalIndex < _horizontalSize)
                throw EmptyDataException(verticalIndex + 1, horizontalIndex, _fileAsStringArray[verticalIndex + 1], "Too few cells in a row.");
            ++verticalIndex;
        }
        if (verticalIndex < _horizontalSize)
            throw EmptyDataException(verticalIndex, 0, "", "Too few rows.");
    }



public:
    StringArrayReader() = default;

    explicit StringArrayReader(const FileReader &fileReader) {
        _fileAsStringArray = fileReader.getLines();
        _verticalSize = 0;
        _horizontalSize = 0;
        parseColumnHeaders();
        parseRowHeaders();
        parseTableCells();
    }

    [[nodiscard]] std::vector<ColumnHeader> getColumnHeaders() const {
        return _columnHeaders;
    }

    [[nodiscard]] std::vector<RowHeader> getRowHeaders() const {
        return _rowHeaders;
    }

    [[nodiscard]] std::vector<std::vector<std::string>> getTableCells() const {
        return _tableCells;
    }
};


#endif //TESTTASK_STRINGARRAYREADER_CPP
