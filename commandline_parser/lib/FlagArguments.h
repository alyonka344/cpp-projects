#pragma once
#include <iostream>
#include <utility>

class FlagArguments {
public:
    explicit FlagArguments(char short_param, std::string long_param = "", std::string description = "") {
        short_param_ = short_param;
        long_param_ = std::move(long_param);
        *flag_ = false;
        description_ = std::move(description);
    }

    char GetShortParam() const;
    std::string GetLongParam();
    bool GetFlag();
    std::string GetDescription();
    bool GetDefaultFlag() const;

    void SetFlag(bool flag);

    void Default(bool value);
    void StoreValue(bool& value);

private:
    char short_param_;
    std::string long_param_;
    bool* flag_ = new bool;
    std::string description_;
    bool default_flag = false;
};