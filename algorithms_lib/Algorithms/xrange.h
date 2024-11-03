#pragma once

#include "AdditionalClasses/XRangeClass.h"

const int kDefaultStep = 1;

template<typename Type>
XRangeClass<Type> xrange(Type end) {
    int step = kDefaultStep;
    if (end < 0) {
        step = -kDefaultStep;
    }
    return XRangeClass<Type>(0, end, step);
}

template<typename Type>
XRangeClass<Type> xrange(Type begin, Type end) {
    int step = kDefaultStep;
    if (end < begin) {
        step = -kDefaultStep;
    }
    return XRangeClass<Type>((begin), static_cast<Type>(end), step);
}

template<typename Type, typename StepType>
XRangeClass<StepType> xrange(Type begin, Type end, StepType step) {
    if ((end < begin && step > 0) || (end > begin && step < 0)) {
        throw std::runtime_error("Wrong arguments");
    }
    return XRangeClass<StepType>(static_cast<StepType>(begin), static_cast<StepType>(end), step);
}