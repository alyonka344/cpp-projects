#include "IntArguments.h"

char IntArguments::GetShortParam() const {
    return short_param_;
}

std::string IntArguments::GetLongParam() {
    return long_param_;
}

int IntArguments::GetValue() {
    return *int_value_;
}

std::vector<int> IntArguments::GetValues() {
    return *int_values_;
}

std::string IntArguments::GetDescription() {
    return description_;
}

bool IntArguments::GetMultiValue() const {
    return multi_value;
}

size_t IntArguments::GetMinArgsCount() const {
    return min_args_count_;
}

bool IntArguments::GetPositional() const {
    return positional;
}

bool IntArguments::GetDefaultFlag() const {
    return default_flag;
}

void IntArguments::SetValue(int value) {
    *int_value_ = value;
}

void IntArguments::SetValues(int value) {
    int_values_->push_back(value);
}

void IntArguments::Default(const int& value) {
    default_flag = true;
    *int_value_ = value;
}

void IntArguments::StoreValue(int& value) {
    int_value_ = &value;
}

void IntArguments::StoreValue(std::vector<int>& int_values) {
    int_values_ = &int_values;
}

void IntArguments::StoreValues(std::vector<int>& int_values) {
    int_values_ = &int_values;
}

IntArguments& IntArguments::MultiValue(int min_args_count) {
    multi_value = true;
    min_args_count_ = min_args_count;

    return *this;
}

IntArguments& IntArguments::Positional() {
    positional = true;
    return *this;
}
