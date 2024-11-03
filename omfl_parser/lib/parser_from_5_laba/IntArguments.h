#pragma once
#include <iostream>
#include <utility>
#include <vector>

class IntArguments {
public:
    explicit IntArguments(char short_param, std::string long_param = "", std::string description = "") {
        short_param_ = short_param;
        long_param_ = std::move(long_param);
        description_ = std::move(description);
    }

    char GetShortParam() const;
    std::string GetLongParam();
    int GetValue();
    std::vector<int> GetValues();
    std::string GetDescription();
    bool GetMultiValue() const;
    size_t GetMinArgsCount() const;
    bool GetPositional() const;
    bool GetDefaultFlag() const;

    void SetValue(int value);
    void SetValues(int value);

    void Default(const int& value);
    void StoreValue(int& value);
    void StoreValue(std::vector<int>& int_values);
    void StoreValues(std::vector<int>& int_values);
    IntArguments& MultiValue(int min_args_count = 0);
    IntArguments& Positional();

private:
    char short_param_ = 0;
    std::string long_param_;
    int* int_value_ = new int;
    std::vector<int>* int_values_ = new std::vector<int>;
    std::string description_;
    bool multi_value = false;
    size_t min_args_count_ = 0;
    bool positional = false;
    bool default_flag = false;
};