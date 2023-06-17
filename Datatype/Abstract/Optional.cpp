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
            delete _value;
            _value = nullptr;
            _hasValue = false;
            return;
        }

        delete _value;
        _value = new dtype(*value);
        *_value = dtype(*value);
        _hasValue = true;
    }

    Optional<dtype>(const Optional<dtype> &cpd) {
        _value = nullptr;
        if (cpd._value != nullptr)
            _value = new dtype(*(cpd._value));
        _hasValue = cpd._hasValue;
    }

    ~Optional() {
        setValue(nullptr);
    }
};


#endif //TESTTASK_OPTIONAL_CPP
