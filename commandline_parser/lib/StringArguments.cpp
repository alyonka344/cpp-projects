#include "StringArguments.h"

#include <utility>

char StringArguments::GetShortParam() const {
    return short_param_;
}

std::string StringArguments::GetLongParam() {
    return long_param_;
}

std::string StringArguments::GetValue() {
    return *string_value_;
}

std::vector<std::string> StringArguments::GetValues() {
    return *string_values_;
}

std::string StringArguments::GetDescription() {
    return description_;
}

bool StringArguments::GetMultiValue() {
    return multi_value;
}

size_t StringArguments::GetMinArgsCount() {
    return min_args_count_;
}

bool StringArguments::GetPositional() const {
    return positional;
}

bool StringArguments::GetDefaultFlag() {
    return default_flag;
}

void StringArguments::SetValue(std::string value) {
    *string_value_ = std::move(value);
}

void StringArguments::SetValues(const std::string& value) {
    string_values_->push_back(value);
}

void StringArguments::Default(const std::string& value) {
    default_flag = true;
    SetValue(value);
}

void StringArguments::StoreValue(std::string& value) {
    string_value_ = &value;
}

void StringArguments::StoreValues(std::vector<std::string>& string_values) {
    string_values_ = &string_values;
}

StringArguments& StringArguments::MultiValue(int min_args_count) {
    multi_value = true;
    min_args_count_ = min_args_count;

    return *this;
}

StringArguments& StringArguments::Positional() {
    positional = true;
    return *this;
}
