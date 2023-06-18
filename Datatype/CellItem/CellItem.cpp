//
// Created by elfxe on 10.06.2023.
//

#ifndef TESTTASK_CELLITEM_CPP
#define TESTTASK_CELLITEM_CPP

#include "../Abstract/Optional.cpp"
#include "../TableHeader/RowHeader.cpp"
#include "../TableHeader/ColumnHeader.cpp"

#include "../../Exception/InvalidCellTreeException.cpp"
#include "../../Exception/ZeroDivisionException.cpp"

enum CellItemType {
    formula = 0,
    value,
    add,
    subtract,
    multiply,
    divide,
    equality
};

enum CellStatus {
    await = 0,
    calculating
};

template<typename dtype>
class CellItem {
private:
    RowHeader _rowHeader;
    ColumnHeader _columnHeader;

    CellItemType _originalCellType;

    Optional<dtype> _value;
    std::string _formula;

    CellItem<dtype> *_left;
    CellItem<dtype> *_right;

    static bool validateFormula(const std::string &value) {
        std::regex regexMatcher(CELL_FORMULA_REGEX_MATCHER);
        return std::regex_match(value, regexMatcher);
    }

    static bool validateValue(const std::string &value) {
        std::regex regexMatcher(CELL_VALUE_REGEX_MATCHER);
        return std::regex_match(value, regexMatcher);
    }

public:
    CellItemType cellItemType;
    CellStatus cellStatus;

    explicit CellItem(const RowHeader &rowHeader, const ColumnHeader &columnHeader, CellItemType cellType) {
        _originalCellType = cellType;
        _rowHeader = rowHeader;
        _columnHeader = columnHeader;
        _left = nullptr;
        _right = nullptr;
        cellItemType = cellType;
        cellStatus = CellStatus::await;
    }

    explicit CellItem(const RowHeader &rowHeader, const ColumnHeader &columnHeader, CellItemType cellType, const std::string &value, dtype(*stringToTypeMapper)(const std::string &)) {
        _rowHeader = rowHeader;
        _columnHeader = columnHeader;
        _left = nullptr;
        _right = nullptr;
        _formula = value;
        _value = Optional<dtype>();
        cellItemType = cellType;
        cellStatus = CellStatus::await;

        if (cellType == CellItemType::value) {
            if (!validateValue(value))
                throw InvalidDataPatternException(rowHeader.getIndexValue(), columnHeader.getIndexValue(), value, "Invalid value format met.");
            dtype tmp = stringToTypeMapper(value);
            _value.setValue(&tmp);
        }

        if (cellType == CellItemType::formula) {
            if (!validateFormula(value))
                throw InvalidDataPatternException(rowHeader.getIndexValue(), columnHeader.getIndexValue(), value, "Invalid formula format met.");

            std::string formulaValue = value;
            formulaValue.erase(formulaValue.begin()); // erasing '=' symbol
            _formula = formulaValue;
        }

        _originalCellType = cellType;
    }

    [[nodiscard]] RowHeader getRowHeader() const {
        return _rowHeader;
    }

    [[nodiscard]] ColumnHeader getColumnHeader() const {
        return _columnHeader;
    }

    CellItem<dtype> *getLeft() const {
        return _left;
    }

    CellItem<dtype> *getRight() const {
        return _right;
    }

    [[nodiscard]] std::string getFormula() const {
        return _originalCellType == CellItemType::formula ? "=" + _formula : _formula;
    }

    void calculateValue() {
        if (cellItemType == CellItemType::value)
            return;

        if (cellItemType != CellItemType::equality && ((_left != nullptr && _left->cellItemType != CellItemType::value) || (_right != nullptr && _right->cellItemType != CellItemType::value) || (_left ==
                nullptr && _right == nullptr)) )
            throw InvalidCellTreeException(_rowHeader.getIndexValue(), _columnHeader.getIndexValue(), _formula, "Required cells were not calculated yet (or were not loaded), but current cell calculation is requested.");

        if (cellItemType == CellItemType::equality && ((_left != nullptr && _right != nullptr) || (_left == nullptr && _right == nullptr)))
            throw InvalidCellTreeException(_rowHeader.getIndexValue(), _columnHeader.getIndexValue(), _formula, "Cell is equal to two (or more) cells.");

        dtype result;
        switch (cellItemType) {
            case CellItemType::formula: {
                throw InvalidCellTreeException(_rowHeader.getIndexValue(), _columnHeader.getIndexValue(), _formula, "Required cells were not calculated yet (contains formula), but current cell calculation is requested.");
            }

            case CellItemType::equality: {
                if (_left != nullptr) {
                    _left->calculateValue();
                    result = *(_left->getValue());
                } else if (_right != nullptr) {
                    _right->calculateValue();
                    result = *(_right->getValue());
                }
                break;
            }

            case CellItemType::add: {
                result = *(_left->getValue()) + *(_right->getValue());
                break;
            }

            case CellItemType::subtract: {
                result = *(_left->getValue()) - *(_right->getValue());
                break;
            }

            case CellItemType::multiply: {
                result = *(_left->getValue()) * *(_right->getValue());
                break;
            }

            case CellItemType::divide: {
                if (*(_right->getValue()) == 0)
                    throw ZeroDivisionException(_rowHeader.getIndexValue(), _columnHeader.getIndexValue(), _formula, "Zero division.");
                result = *(_left->getValue()) / *(_right->getValue());
                break;
            }
        }
        _value.setValue(&result);
        cellItemType = CellItemType::value;
    }

    dtype *getValue() const {
        return _value.getValue();
    }

    void setLeft(CellItem<dtype> *left) {
        _left = left;
    }

    void setRight(CellItem<dtype> *right) {
        _right = right;
    }
};


#endif //TESTTASK_CELLITEM_CPP
