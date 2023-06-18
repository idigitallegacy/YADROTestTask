//
// Created by elfxe on 13.06.2023.
//

#ifndef TESTTASK_TABLEEXECUTOR_CPP
#define TESTTASK_TABLEEXECUTOR_CPP

#include <string>
#include <iostream>
#include "../IOReader/File/FileReader.cpp"
#include "Table.cpp"

#include "../../Exception/FileNotPermittedException.cpp"


template<typename dtype>
class TableExecutor {
private:
    FileReader _fileReader;
    StringArrayReader _stringArrayReader;
    Table<dtype> _table;


public:
    explicit TableExecutor(std::ifstream &fileStream, dtype(*stringToTypeMapper)(const std::string &)) {
        try {
            _fileReader = FileReader(fileStream);
            _stringArrayReader = StringArrayReader(_fileReader);
            _table = Table<dtype>(_stringArrayReader, stringToTypeMapper);
        } catch (FileNotPermittedException &exception) {
            std::cout << "Unable to open file" << ":\n"
                      << '\t' << exception.what();
            throw;
        } catch (EmptyDataException &exception) {
            std::cout << "Unable to read table at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.line() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (InvalidDataPatternException &exception) {
            std::cout << "Invalid data/header pattern at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.value() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (InvalidCellTreeException &exception) {
            std::cout << "Unable to calculate cell at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.cellValue() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (ZeroDivisionException &exception) {
            std::cout << "Zero division reached at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.cellValue() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (InvalidOperatorException &exception) {
            std::cout << "Invalid operator caught at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.value() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (SelfReferenceException &exception) {
            std::cout << "Self-referenced cell at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.value() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        } catch (InvalidCellAddressException &exception) {
            std::cout << "Invalid requested cell address at line " << exception.lineNumber() << ", column "
                      << exception.columnNumber() << ": \n"
                      << '\'' << exception.value() << '\'' << '\n'
                      << '\t' << exception.what();
            throw;
        }
    }

    void writeTableToConsole(std::string(*typeToStingMapper)(const dtype *)) {
        std::vector<std::vector<std::string>> valueArray = _table.getFormattedTable(typeToStingMapper);
        for (auto &row: valueArray) {
            std::string &lastCell = row[row.size() - 1];
            for (auto &cell: row) {
                if (&cell == &lastCell)
                    std::cout << cell;
                else
                    std::cout << cell << ',';
            }
            std::cout << '\n';
        }
    }

    std::string getTable(std::string(*typeToStingMapper)(const dtype *)) {
        std::string result;
        std::vector<std::vector<std::string>> valueArray = _table.getFormattedTable(typeToStingMapper);
        for (auto &row: valueArray) {
            std::string &lastCell = row[row.size() - 1];
            for (auto &cell: row) {
                if (&cell == &lastCell)
                    result += cell;
                else
                    result += cell + ',';
            }
            result += '\n';
        }
        return result;
    }
};


#endif //TESTTASK_TABLEEXECUTOR_CPP
