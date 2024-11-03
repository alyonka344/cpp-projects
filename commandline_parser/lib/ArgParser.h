#pragma once
#include "FlagArguments.h"
#include "HelpArguments.h"
#include "IntArguments.h"
#include "StringArguments.h"

#include <vector>

namespace ArgumentParser {

class ArgParser {
public:
    explicit ArgParser(const std::string& parser_name) {
        parser_name_ = parser_name;
    }

    bool Parse(const std::vector<std::string>& split_string);
    bool Parse(int argc, char** argv);

    StringArguments& AddStringArgument(char param1 = 0, const std::string& param2 = "", const std::string& description = "");
    StringArguments& AddStringArgument(const std::string& param, const std::string& description = "");

    IntArguments& AddIntArgument(char param1 = 0, const std::string& param2 = "", const std::string& description = "");
    IntArguments& AddIntArgument(const std::string& param, const std::string& description = "");

    FlagArguments& AddFlag(char param1 = 0, const std::string& param2 = "", const std::string& description = "");
    FlagArguments& AddFlag(const std::string& param2, const std::string& description = "");

    std::string GetStringValue(const std::string& param);
    std::string GetStringValue(const std::string& param, int index);

    int GetIntValue(const std::string& param);
    int GetIntValue(const std::string& param, int index);

    bool GetFlag(const std::string& param);

    void AddHelp(const char& short_name, const std::string& long_name, const std::string& description);
    bool Help() const;
    std::string HelpDescription();

private:
    std::string parser_name_;
    std::vector<StringArguments> string_args;
    std::vector<IntArguments> int_args;
    std::vector<FlagArguments> flags;
    HelpArguments help_args;
    bool help_flag = false;

    bool SetToDefaultValue();
    bool PositionalMultiIntValue();
    bool PositionalMultiStringValue();
};

} // namespace ArgumentParser