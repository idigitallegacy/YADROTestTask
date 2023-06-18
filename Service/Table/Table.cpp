//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_TABLE_CPP
#define TESTTASK_TABLE_CPP

#include <vector>
#include "../../cfg.h"
#include "../../Datatype/TableHeader/RowHeader.cpp"
#include "../../Datatype/TableHeader/ColumnHeader.cpp"
#include "../../Datatype/CellItem/CellItem.cpp"
#include "../IOReader/StringArray/StringArrayReader.cpp"

#include "../../Exception/InvalidOperatorException.cpp"
#include "../../Exception/SelfReferenceException.cpp"
#include "../../Exception/InvalidCellAddressException.cpp"

template<typename dtype>
class Table {
private:
    const std::vector<char> _supportedOperators = {'+', '-', '/', '*'};
    std::vector<RowHeader> _rowHeaders;
    std::vector<ColumnHeader> _columnHeaders;
    std::vector<std::vector<std::vector<CellItem<dtype>>>> _hashtable;

    static INDEX_T hash(const std::string &header) {
        INDEX_T h = 0;
        INDEX_T pos = 1;
        const INDEX_T k = 59;
        const INDEX_T mod = 17002481;
        for (char letter: header) {
            INDEX_T x = ((INDEX_T) letter - (INDEX_T) '0' + (INDEX_T) 1) * pos;
            h = (h * k + x) % mod;
            ++pos;
        }
        return h % TABLE_MAX_ELEMENTS;
    }

    std::string formatFormula(const std::string &formula) {
        // Only removes whitespaces and '=' symbol
        std::string formattedFormula;
        for (auto &letter : formula) {
            if (letter != ' ')
                formattedFormula.push_back(letter);
        }
        formattedFormula.erase(formattedFormula.begin());
        return formattedFormula;
    }

    std::pair<std::string, std::string> splitCellAddress(const std::string &cellAddress) {
        std::string rowAddress;
        std::string columnAddress;

        for (auto &letter: cellAddress) {
            if ((letter - 'A' >= 0 && letter - 'Z' <= 0) || (letter - 'a' >= 0 && letter - 'z' <= 0))
                columnAddress += letter;
            else if (letter - '0' >= 0 && letter - '9' <= 0)
                rowAddress += letter;
            else
                throw InvalidDataPatternException(UNDEFINED_CELL_INDEX, UNDEFINED_CELL_INDEX, cellAddress, (&"Unknown symbol at cell address: " [ letter]));
        }
        return std::make_pair(rowAddress, columnAddress);
    }

    CellItem<dtype> *findCellAddress(const std::string &cellAddress) {
        std::pair<std::string, std::string> cellRowAndColumn = splitCellAddress(cellAddress);

        INDEX_T rowIndex = hash(cellRowAndColumn.first);
        INDEX_T columnIndex = hash(cellRowAndColumn.second);

        for (int i = 0; i < _hashtable[rowIndex][columnIndex].size(); ++i) {
            if (_hashtable[rowIndex][columnIndex][i].getRowHeader().getStringValue() == cellRowAndColumn.first &&
                _hashtable[rowIndex][columnIndex][i].getColumnHeader().getStringValue() == cellRowAndColumn.second)
                return &_hashtable[rowIndex][columnIndex][i];
        }

        throw InvalidCellAddressException(UNDEFINED_CELL_INDEX, UNDEFINED_CELL_INDEX, "", ("Invalid requested cell address: " + cellAddress).c_str());
    }

    CellItem<dtype> *calculateTree(CellItem<dtype> *treeRoot) {
        if (treeRoot->cellItemType == CellItemType::value) {
            treeRoot->cellStatus = CellStatus::await;
            return treeRoot;
        }

        if (treeRoot->getLeft() != nullptr)
            treeRoot->setLeft(calculateTree(treeRoot->getLeft()));
        if (treeRoot->getRight() != nullptr)
            treeRoot->setRight(calculateTree(treeRoot->getRight()));
        treeRoot->calculateValue();

        treeRoot->cellStatus = CellStatus::await;
        return treeRoot;
    }

    CellItem<dtype> *parseFormula(CellItem<dtype> *cell, dtype(*stringToTypeMapper)(const std::string &), long long recursionDepth = 0) {
        // TODO: Parse pairs in the right order to follow the operators' priority (if the cell contains more than 1 operator)
        // If the cells are indirectly self-referenced, it leads to infinite recursion. If the default check doesn't pass, this will.
        if (recursionDepth > MAX_RECURSION_DEPTH && MAX_RECURSION_DEPTH != 0)
            throw SelfReferenceException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), "Recursion depth limit exceed. May be, self referenced cell.");

        if (cell->cellItemType == CellItemType::value) {
            cell->cellStatus = CellStatus::await;
            return cell;
        }

        cell->cellStatus = CellStatus::calculating;

        std::string requestedCellAddress;
        std::string formula = formatFormula(cell->getFormula());

        CellItem<dtype> *previousCell = nullptr;
        char previousOperator = '\0';
        INDEX_T index = -1;

        for (auto &letter: formula) {
            ++index;

            if (std::find(_supportedOperators.begin(), _supportedOperators.end(), letter) ==
                _supportedOperators.end()) {
                requestedCellAddress += letter;
                if (index != formula.size() - 1)
                    continue;
            }

            std::regex regexValueMatcher(CELL_VALUE_REGEX_MATCHER);
            std::regex regexCellMatcher(CELL_FORMULA_VALUE_REGEX_MATCHER);

            CellItem<dtype> *requestedCell = nullptr;
            CellItem<dtype> *requestedOperator = nullptr;

            if (std::regex_match(requestedCellAddress, regexCellMatcher)) {
                try {
                    requestedCell = findCellAddress(requestedCellAddress);
                } catch (InvalidDataPatternException &exception) {
                    throw InvalidDataPatternException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), exception.what());
                } catch (InvalidCellAddressException &exception) {
                    throw InvalidCellAddressException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), exception.what());
                }
            } else
                requestedCell = new CellItem<dtype>(cell->getRowHeader(), cell->getColumnHeader(), CellItemType::value, requestedCellAddress, stringToTypeMapper);

            // If cell is indirectly self-referenced
            if (requestedCell->cellStatus == CellStatus::calculating)
                throw SelfReferenceException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), "Self referenced cell.");

            // If cell is directly self-referenced
            if (requestedCell == cell)
                throw SelfReferenceException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), "Self referenced cell.");

            // Building first operable cell
            if (previousCell == nullptr) {
                if (previousOperator == '\0')
                    previousOperator = letter;

                switch (previousOperator) {
                    case '+': {
                        cell->cellItemType = CellItemType::add;
                        break;
                    }
                    case '-': {
                        cell->cellItemType = CellItemType::subtract;
                        break;
                    }
                    case '*': {
                        cell->cellItemType = CellItemType::multiply;
                        break;
                    }
                    case '/': {
                        cell->cellItemType = CellItemType::divide;
                        break;
                    }
                    default: {
                        if (index != formula.size() - 1)
                            throw InvalidOperatorException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), (&"Unknown operator: " [ previousOperator]));
                    }
                }


                CellItem<dtype> *parsedSubcell = parseFormula(requestedCell, stringToTypeMapper, recursionDepth + 1);
                parsedSubcell->cellStatus = CellStatus::await;

                if (cell->getLeft() == nullptr)
                    cell->setLeft(parsedSubcell);
                else
                    cell->setRight(parsedSubcell);

                // If the formula contains only one cell
                if (index == formula.size() - 1 && (cell->getRight() == nullptr)) {
                    cell->cellItemType = CellItemType::equality;
                    return cell;
                }

                if (cell->getLeft() == nullptr || cell->getRight() == nullptr) {
                    requestedCellAddress.clear();
                    previousOperator = letter;
                    continue;
                }
                previousCell = cell;
                requestedCellAddress.clear();
                previousOperator = letter;
                continue;
            }

            // Building the rest cells
            switch (previousOperator) {
                case '+': {
                    requestedOperator = new CellItem<dtype>(cell->getRowHeader(), cell->getColumnHeader(),
                                                            CellItemType::add);
                    break;
                }
                case '-': {
                    requestedOperator = new CellItem<dtype>(cell->getRowHeader(), cell->getColumnHeader(),
                                                            CellItemType::subtract);
                    break;
                }
                case '*': {
                    requestedOperator = new CellItem<dtype>(cell->getRowHeader(), cell->getColumnHeader(),
                                                            CellItemType::multiply);
                    break;
                }
                case '/': {
                    requestedOperator = new CellItem<dtype>(cell->getRowHeader(), cell->getColumnHeader(),
                                                            CellItemType::divide);
                    break;
                }
                    // Unrecognized operator
                default: {
                    if (index != formula.size() - 1)
                        throw InvalidOperatorException(cell->getRowHeader().getIndexValue(), cell->getColumnHeader().getIndexValue(), cell->getFormula(), (&"Unknown operator: " [ previousOperator]));
                }
            }

            CellItem<dtype> *parsedSubcell = parseFormula(requestedCell, stringToTypeMapper, recursionDepth + 1);
            parsedSubcell->cellStatus = CellStatus::await;

            requestedOperator->setLeft(previousCell);
            requestedOperator->setRight(parsedSubcell);

            previousCell = requestedOperator;
            requestedCellAddress.clear();
            previousOperator = letter;
        }

        return previousCell;
    }

    CellItem<dtype> parseCell(const RowHeader &rowHeader, const ColumnHeader &columnHeader, const std::string &value, dtype(*stringToTypeMapper)(const std::string &)) {
        if (value[0] == '=') {
            return CellItem<dtype>(rowHeader, columnHeader, CellItemType::formula, value, stringToTypeMapper);
        }

        return CellItem<dtype>(rowHeader, columnHeader, CellItemType::value, value, stringToTypeMapper);
    }

    void parseCells(const std::vector<std::vector<std::string>> &cells, dtype(*stringToTypeMapper)(const std::string &)) {
        for (INDEX_T y = 0; y < _rowHeaders.size(); ++y) {
            for (INDEX_T x = 0; x < _columnHeaders.size(); ++x) {
                INDEX_T rowHash = hash(_rowHeaders[y].getStringValue());
                INDEX_T columnHash = hash(_columnHeaders[x].getStringValue());
                _hashtable[rowHash][columnHash].push_back(parseCell(_rowHeaders[y], _columnHeaders[x], cells[y][x], stringToTypeMapper));
            }
        }
    }

    void buildHashtable() {
        _hashtable.resize(TABLE_MAX_ELEMENTS);
        for (auto &i: _hashtable)
            i.resize(TABLE_MAX_ELEMENTS);
    }

    void calculateCells(dtype(*stringToTypeMapper)(const std::string &)) {
        for (auto &rowHeader : _rowHeaders) {
            for (auto &columnHeader : _columnHeaders) {
                INDEX_T rowIndex = hash(rowHeader.getStringValue());
                INDEX_T columnIndex = hash(columnHeader.getStringValue());

                for (INDEX_T i = 0; i < _hashtable[rowIndex][columnIndex].size(); ++i) {
                    if (_hashtable[rowIndex][columnIndex][i].getRowHeader().getStringValue() == rowHeader.getStringValue() &&
                        _hashtable[rowIndex][columnIndex][i].getColumnHeader().getStringValue() == columnHeader.getStringValue()) {
                        CellItem<dtype> *cellTree = parseFormula(&(_hashtable[rowIndex][columnIndex][i]), stringToTypeMapper);
                        _hashtable[rowIndex][columnIndex][i] = *calculateTree(cellTree);
                    }
                }
            }
        }
    }

public:
    Table() = default;

    explicit Table(const StringArrayReader &stringArrayReader, dtype(*stringToTypeMapper)(const std::string &)) {
        _rowHeaders = stringArrayReader.getRowHeaders();
        _columnHeaders = stringArrayReader.getColumnHeaders();

        _hashtable = std::vector<std::vector<std::vector<CellItem<dtype>>>>();
        buildHashtable();
        parseCells(stringArrayReader.getTableCells(), stringToTypeMapper);
        calculateCells(stringToTypeMapper);
    }

    std::vector<std::vector<std::string>> getFormattedTable(std::string(*typeToStingMapper)(const dtype *)) {
        std::vector<std::vector<std::string>> result = std::vector<std::vector<std::string>>();

        result.emplace_back();
        result[0].emplace_back("");
        for (auto &columnHeader : _columnHeaders) {
            result[0].push_back(columnHeader.getStringValue());
        }

        INDEX_T rowIndex = 1;
        INDEX_T columnIndex = 0;
        for (auto &rowHeader : _rowHeaders) {
            result.emplace_back();
            result[rowIndex].push_back(rowHeader.getStringValue());
            for (auto &columnHeader : _columnHeaders) {
                INDEX_T rowCellIndex = hash(rowHeader.getStringValue());
                INDEX_T columnCellIndex = hash(columnHeader.getStringValue());

                for (INDEX_T i = 0; i < _hashtable[rowCellIndex][columnCellIndex].size(); ++i) {
                    if (_hashtable[rowCellIndex][columnCellIndex][i].getRowHeader().getStringValue() == rowHeader.getStringValue() &&
                        _hashtable[rowCellIndex][columnCellIndex][i].getColumnHeader().getStringValue() == columnHeader.getStringValue()) {
                        result[rowIndex].push_back(typeToStingMapper(_hashtable[rowCellIndex][columnCellIndex][i].getValue()));
                    }
                }
                ++columnIndex;
            }
            ++rowIndex;
            columnIndex = 0;
        }

        return result;
    }

    Table<dtype>& operator=(Table<dtype>&&cpd) noexcept {
        _rowHeaders = cpd._rowHeaders;
        _columnHeaders = cpd._columnHeaders;
        _hashtable = cpd._hashtable;
        return *this;
    }
};


#endif //TESTTASK_TABLE_CPP
