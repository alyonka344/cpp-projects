#pragma once

#include "AdditionalClasses/ZipClass.h"

template<typename Type1, typename Type2>
ZipClass<Type1, Type2> zip(Type1& first_container, Type2& second_container) {
    return ZipClass<Type1, Type2>(first_container, second_container);
}