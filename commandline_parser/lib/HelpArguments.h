#pragma once
#include <iostream>

class HelpArguments {
public:
    explicit HelpArguments(char short_param = 0, std::string long_param = "", std::string description = "") {
        long_param_ = std::move(long_param);
        short_param_ = short_param;
        description_ = std::move(description);
    }

    char GetShortParam() const;
    std::string GetLongParam();
    std::string GetDescription();

private:
    char short_param_;
    std::string long_param_;
    std::string description_;
};