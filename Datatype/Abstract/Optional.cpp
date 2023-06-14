//
// Created by elfxe on 08.06.2023.
//

#include <cstdlib>
#include "Optional.h"

template<class dtype>
Optional<dtype>::Optional() {
    _value = nullptr;
    _hasValue = false;
}

template<class dtype>
Optional<dtype>::Optional(dtype value) {
    _value = new dtype(value);
    _hasValue = true;
}

template<class dtype>
bool Optional<dtype>::hasValue() const {
    return _hasValue;
}

template<class dtype>
dtype *Optional<dtype>::getValue() const {
    if (_hasValue)
        return _value;
    return nullptr;
}

template<class dtype>
void Optional<dtype>::setValue(dtype *value) {
    if (value == nullptr) {
        _hasValue = false;
        return;
    }

    if (_value == nullptr)
        _value = new dtype(*value);
    *_value = dtype(*value);
    _hasValue = true;
}

template<class dtype>
void Optional<dtype>::removeValue() {
    delete _value;
    _value = nullptr;
    _hasValue = false;
}

