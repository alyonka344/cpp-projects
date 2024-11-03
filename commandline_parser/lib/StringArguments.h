#pragma once
#include <iostream>
#include <utility>
#include <vector>

class StringArguments {
public:
    explicit StringArguments(char short_param, std::string long_param = "", std::string description = "") {
        short_param_ = short_param;
        long_param_ = std::move(long_param);
        description_ = std::move(description);
    }

    char GetShortParam() const;
    std::string GetLongParam();
    std::string GetValue();
    std::vector<std::string> GetValues();
    std::string GetDescription();
    bool GetMultiValue();
    size_t GetMinArgsCount();
    bool GetPositional() const;
    bool GetDefaultFlag();

    void SetValue(std::string value);
    void SetValues(const std::string& value);

    void Default(const std::string& value);
    void StoreValue(std::string& value);
    void StoreValues(std::vector<std::string>& int_values);
    StringArguments& MultiValue(int min_args_count = 0);
    StringArguments& Positional();

private:
    char short_param_ = 0;
    std::string long_param_;
    std::string* string_value_ = new std::string;
    std::vector<std::string>* string_values_ = new std::vector<std::string>;
    std::string description_;
    bool multi_value = false;
    size_t min_args_count_ = 0;
    bool positional = false;
    bool default_flag = false;
};