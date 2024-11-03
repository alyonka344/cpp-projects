#include "number.h"
#include <iostream>
#include <cstring>

const size_t size_arr = 70;

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;

    if (i < 1000000000) {
        result.number[size_arr - 1] = i;
        result.count = 1;
    }
    else {
        result.number[size_arr - 2] = i / 1000000000;
        result.number[size_arr - 1] = i % 1000000000;
        result.count = 2;
    }
    return result;
}

uint2022_t from_string(const char* buff) {
    unsigned length = std::strlen(buff);
    uint2022_t result;

    unsigned first_count = length % 9;
    length = length - length % 9;
    unsigned n = length / 9;

    if (first_count != 0) {
        for (int j = 0; j < first_count; j++)
            result.number[size_arr - n - 1] = result.number[size_arr - n - 1]*10 + buff[j] - '0';
        result.count++;
    }

    int ind = 0;
    for (unsigned j = 0; j < n; j ++) {
        for (int k = 0; k < 9; k++) {
            result.number[size_arr - n + j] = result.number[size_arr - n + j]*10 + buff[first_count + ind] - '0';
            ind++;
        }
    }
    result.count += n;

    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;

    uint32_t im = 0;
    result.count = std::max(lhs.count, rhs.count);
    for (int i = 1; i <= result.count; i++) {
        result.number[size_arr - i] = (lhs.number[size_arr - i] + rhs.number[size_arr - i] + im) % 1000000000;
        im = (lhs.number[size_arr - i] + rhs.number[size_arr - i] + im) / 1000000000;
    }
    if (im > 0) {
        result.count++;
        result.number[size_arr - result.count] = im;
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;

    uint32_t im = 0;
    for (int i = 1; i <= lhs.count; i++) {
        if ((lhs.number[size_arr - i] >= rhs.number[size_arr - i]) && lhs.number[size_arr - i] != 0) {
            if (lhs.number[size_arr - i] - im / 1000000000 < rhs.number[size_arr - i]) {
                im = 1000000000;
                result.number[size_arr - i] = (lhs.number[size_arr - i] - im / 1000000000 + im - rhs.number[size_arr - i]);
            }
            else {
                result.number[size_arr - i] = (lhs.number[size_arr - i] - im / 1000000000 - rhs.number[size_arr - i]);
                im = 0;
            }
        }
        else if (lhs.number[size_arr - i] == 0 && im > 0) {
            result.number[size_arr - i] = (999999999 - rhs.number[size_arr - i]);
        }
        else {
            im = 1000000000;
            result.number[size_arr - i] = (lhs.number[size_arr - i] + im - rhs.number[size_arr - i]);
        }
    }

    result.count = size_arr;
    int i = 0;
    while (result.number[i] == 0) {
        result.count--;
        i++;
    }

    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint2022_t add_number;

    uint32_t im = 0;
    for (int j = 0; j < rhs.count; j++) {
        add_number.count = j;
        for (int k = 0; k < lhs.count; k++) {
            long long number_1 = lhs.number[size_arr - 1 - k];
            long long number_2 = rhs.number[size_arr - 1 - j];
            long long number = number_1 * number_2;
            add_number.number[size_arr - k - j - 1] = (number + im) % 1000000000;
            add_number.count++;
            im = (number + im) / 1000000000;
        }
        if (im > 0) {
            add_number.number[size_arr - j - 1 - lhs.count] = im;
            im = 0;
            add_number.count++;
        }
        result = (result + add_number);
        add_number = {0};
    }

    result.count = size_arr;
    int i = 0;
    while (result.number[i] == 0) {
        result.count--;
        i++;
    }

    return result;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < size_arr; i++) {
        if (lhs.number[i] != rhs.number[i])
            return false;
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < size_arr; i++) {
        if (lhs.number[i] != rhs.number[i])
            return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    for (int i = 0; i < value.count; i++) {
        std::string number = std::to_string(value.number[size_arr - value.count + i]);
        size_t length = std::strlen(&number[0]);
        if ((i != 0) && (length < 9)) {
            size_t n = 9 - length;
            for (int j = 0; j < n; j++)
                stream << 0;
            stream << number;
        }
        else
            stream << number;
    }
    return stream;
}
