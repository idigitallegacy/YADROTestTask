//
// Created by elfxe on 08.06.2023.
//

#ifndef TESTTASK_OPTIONAL_H
#define TESTTASK_OPTIONAL_H

template<class dtype>
class Optional {
private:
    dtype *_value;
    bool _hasValue;

public:
    Optional();

    explicit Optional(dtype value);

    [[nodiscard]] bool hasValue() const;

    dtype *getValue() const;

    void setValue(dtype *value);

    void removeValue();
};


#endif //TESTTASK_OPTIONAL_H
