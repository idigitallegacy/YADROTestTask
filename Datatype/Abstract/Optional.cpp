//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_OPTIONAL_CPP
#define TESTTASK_OPTIONAL_CPP

template<class dtype>
class Optional {
private:
    dtype *_value;
    bool _hasValue;

public:
    Optional() {
        _value = nullptr;
        _hasValue = false;
    }

    explicit Optional(dtype value) {
        _value = new dtype(value);
        _hasValue = true;
    }

    [[nodiscard]] bool hasValue() const {
        return _hasValue;
    }

    dtype *getValue() const {
        if (_hasValue)
            return _value;
        return nullptr;
    }

    void setValue(dtype *value) {
        if (value == nullptr) {
            _hasValue = false;
            return;
        }

        if (_value == nullptr)
            _value = new dtype(*value);
        *_value = dtype(*value);
        _hasValue = true;
    }

    void removeValue() {
        delete _value;
        _value = nullptr;
        _hasValue = false;
    }
};


#endif //TESTTASK_OPTIONAL_CPP
