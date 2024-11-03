#include "ArgParser.h"

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& split_string) {
    bool parse_flag = false;
    for (size_t i = 1; i < split_string.size(); ++i) {
        if (split_string[i][0] == '-' && split_string[i][1] == '-') {
            uint64_t entry_number = split_string[i].find('=');

            if (entry_number != -1) {
                std::string param = split_string[i].substr(2, entry_number - 2);
                std::string value = split_string[i].substr(entry_number + 1);

                for (size_t j = 0; j < string_args.size(); ++j) {
                    if (string_args[j].GetLongParam() == param) {
                        if (string_args[j].GetMultiValue()) {
                            string_args[j].SetValues(value);
                        } else {
                            string_args[j].SetValue(value);
                        }
                        parse_flag = true;
                        break;
                    }
                }
                for (size_t j = 0; j < int_args.size(); ++j) {
                    if (int_args[j].GetLongParam() == param) {
                        int int_value = std::stoi(value);

                        if (int_args[j].GetMultiValue()) {
                            int_args[j].SetValues(int_value);
                        } else {
                            int_args[j].SetValue(int_value);
                        }
                        parse_flag = true;
                        break;
                    }
                }
            }
            else {
                std::string param = split_string[i].substr(2);

                if (help_args.GetLongParam() == param) {
                    help_flag = true;
                    parse_flag = true;
                } else {
                    for (size_t j = 0; j < flags.size(); ++j) {
                        if (flags[j].GetLongParam() == param) {
                            flags[j].SetFlag(true);
                            parse_flag = true;
                            break;
                        }
                    }
                }
            }
        } else if (split_string[i][0] == '-') {
            uint64_t entry_number = split_string[i].find('=');
            if (entry_number != -1) {
                char param = split_string[i][1];
                std::string value = split_string[i].substr(entry_number + 1);
                for (size_t j = 0; j < string_args.size(); ++j) {
                    if (string_args[j].GetShortParam() == param) {
                        if (string_args[j].GetMultiValue()) {
                            string_args[j].SetValues(value);
                        } else {
                            string_args[j].SetValue(value);
                        }
                        parse_flag = true;
                        break;
                    }
                }
                for (size_t j = 0; j < int_args.size(); ++j) {
                    if (int_args[j].GetShortParam() == param) {
                        int int_value = std::stoi(value);
                        if (int_args[j].GetMultiValue()) {
                            int_args[j].SetValues(int_value);
                        } else {
                            int_args[j].SetValue(int_value);
                        }
                        parse_flag = true;
                        break;
                    }
                }
            } else {
                char param = split_string[i][1];
                if (help_args.GetShortParam() == param) {
                    help_flag = true;
                    parse_flag = true;
                }
                for (size_t k = 0; k < split_string[i].length(); ++k) {
                    char param = split_string[i][k];
                    for (size_t j = 0; j < flags.size(); ++j) {
                        if (flags[j].GetShortParam() == param) {
                            flags[j].SetFlag(true);
                            parse_flag = true;
                            break;
                        }
                    }
                }
            }
        } else {
            for (size_t j = 0; j < int_args.size(); ++j) {
                if (int_args[j].GetPositional()) {
                    int value = std::stoi(split_string[i]);

                    if (int_args[j].GetMultiValue()) {
                        int_args[j].SetValues(value);
                    } else {
                        int_args[j].SetValue(value);
                    }
                    parse_flag = true;
                }
            }
            for (size_t j = 0; j < string_args.size(); ++j) {
                if (string_args[j].GetPositional()) {
                    const std::string& value = split_string[i];

                    if (string_args[j].GetMultiValue()) {
                        string_args[j].SetValues(value);
                    } else {
                        string_args[j].SetValue(value);
                    }
                    parse_flag = true;
                }
            }
        }
    }
    if (!PositionalMultiIntValue()) {
        parse_flag = false;
    }
    if (!PositionalMultiStringValue()) {
        parse_flag = false;
    }
    if (string_args.empty() && int_args.empty() && flags.empty() && !Help()) {
        parse_flag = true;
    }
    if (SetToDefaultValue()) {
        parse_flag = true;
    }
    if (help_flag) {
        parse_flag = true;
    }

    return parse_flag;
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> split_string;

    for (int i = 0; i < argc; ++i) {
        std::string element = argv[i];
        split_string.push_back(element);
    }

    return Parse(split_string);
}

StringArguments& ArgumentParser::ArgParser::AddStringArgument(char param1, const std::string& param2, const std::string& description) {
    StringArguments arg(param1, param2, description);
    string_args.push_back(arg);

    return string_args.back();
}

StringArguments& ArgumentParser::ArgParser::AddStringArgument(const std::string& param, const std::string& description) {
    StringArguments arg(0, param, description);
    string_args.push_back(arg);

    return string_args.back();
}

IntArguments& ArgumentParser::ArgParser::AddIntArgument(char param1, const std::string& param2, const std::string& description) {
    IntArguments arg(param1, param2, description);
    int_args.push_back(arg);

    return int_args.back();
}

IntArguments& ArgumentParser::ArgParser::AddIntArgument(const std::string& param, const std::string& description) {
    IntArguments arg(0, param, description);
    int_args.push_back(arg);

    return int_args.back();
}

FlagArguments& ArgumentParser::ArgParser::AddFlag(char param1, const std::string& param2, const std::string& description) {
    FlagArguments arg(param1, param2, description);
    flags.push_back(arg);

    return flags.back();
}

FlagArguments& ArgumentParser::ArgParser::AddFlag(const std::string& param2, const std::string& description) {
    FlagArguments arg(0, param2, description);
    flags.push_back(arg);

    return flags.back();
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& param) {
    std::string value;
    for (size_t i = 0; i < string_args.size(); ++i) {
        if (string_args[i].GetLongParam() == param) {
            value = string_args[i].GetValue();
            break;
        }
    }

    return value;
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& param, int index) {
    std::vector<std::string> value;
    for (size_t i = 0; i < string_args.size(); ++i) {
        if (string_args[i].GetLongParam() == param) {
            value = string_args[i].GetValues();
            break;
        }
    }

    return value[index];
}

int ArgumentParser::ArgParser::GetIntValue(const std::string& param) {
    int value = 0;
    for (size_t i = 0; i < int_args.size(); ++i) {
        if (int_args[i].GetLongParam() == param) {
            value = int_args[i].GetValue();
            break;
        }
    }

    return value;
}

int ArgumentParser::ArgParser::GetIntValue(const std::string& param, int index) {
    std::vector<int> value;
    for (size_t i = 0; i < int_args.size(); ++i) {
        if (int_args[i].GetLongParam() == param) {
            value = int_args[i].GetValues();
            return value[index];
        }
    }

    return 0;
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& param) {
    bool flag = false;
    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i].GetLongParam() == param) {
            flag = flags[i].GetFlag();
            break;
        }
    }

    return flag;
}

void ArgumentParser::ArgParser::AddHelp(const char& short_name, const std::string& long_name, const std::string& description) {
    HelpArguments new_help_arg(short_name, long_name, description);
    help_args = new_help_arg;
}

bool ArgumentParser::ArgParser::Help() const {
    return help_flag;
}

std::string ArgumentParser::ArgParser::HelpDescription() {
    std::string help_description;
    help_description.append(parser_name_);
    help_description += "\n";
    help_description += help_args.GetDescription();
    help_description += "\n\n";

    for (size_t i = 0; i < string_args.size(); ++i) {
        if (string_args[i].GetShortParam() != 0) {
            help_description += '-';
            help_description += string_args[i].GetShortParam();
            help_description += ",  ";
        } else {
            help_description += "    ";
        }
        help_description.append("--" + string_args[i].GetLongParam() + "=<string>");
        if (!string_args[i].GetDescription().empty()) {
            help_description.append(",  " + string_args[i].GetDescription());
        }
        if (string_args[i].GetMultiValue()) {
            help_description += " [repeated, min args = ";
            help_description += std::to_string(string_args[i].GetMinArgsCount());
            help_description += ']';
        }
        if (string_args[i].GetDefaultFlag()) {
            help_description += "[default = ";
            help_description += string_args[i].GetValue();
            help_description += ']';
        }
        help_description += "\n";
    }

    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i].GetShortParam() != 0) {
            help_description += '-';
            help_description += flags[i].GetShortParam();
            help_description += ",  ";
        } else {
            help_description += "    ";
        }
        help_description.append("--" + flags[i].GetLongParam());
        if (!flags[i].GetDescription().empty()) {
            help_description.append(",  " + flags[i].GetDescription());
        }
        if (flags[i].GetDefaultFlag()) {
            if (flags[i].GetFlag()) {
                help_description += " [default = true]";
            }
            else {
                help_description += " [default = false]";
            }
        }
        help_description += "\n";
    }

    for (size_t i = 0; i < int_args.size(); ++i) {
        if (int_args[i].GetShortParam() != 0) {
            help_description += '-';
            help_description += int_args[i].GetShortParam();
            help_description += ",  ";
        } else {
            help_description += "    ";
        }
        help_description.append("--" + int_args[i].GetLongParam() + "=<int>");
        if (!int_args[i].GetDescription().empty()) {
            help_description.append(",  " + int_args[i].GetDescription());
        }
        if (int_args[i].GetMultiValue()) {
            help_description += " [repeated, min args = ";
            help_description += std::to_string(int_args[i].GetMinArgsCount());
            help_description += ']';
        }
        if (int_args[i].GetDefaultFlag()) {
            help_description += " [default = ";
            help_description += std::to_string(int_args[i].GetValue());
            help_description += ']';
        }
        help_description += "\n";
    }
    help_description += "\n";

    if (help_args.GetShortParam() != 0) {
        help_description += '-';
        help_description += help_args.GetShortParam();
        help_description += ", ";
    } else {
        help_description += "    ";
    }
    help_description.append("--" + help_args.GetLongParam());
    if (!help_args.GetDescription().empty()) {
        help_description.append(" Display this help and exit\n");
    }

    return help_description;
}

bool ArgumentParser::ArgParser::SetToDefaultValue() {
    for (size_t i = 0; i < string_args.size(); ++i) {
        if (string_args[i].GetDefaultFlag()) {
            return true;
        }
    }
    for (size_t i = 0; i < int_args.size(); ++i) {
        if (int_args[i].GetDefaultFlag()) {
            return true;
        }
    }
    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i].GetDefaultFlag()) {
            return true;
        }
    }

    return false;
}

bool ArgumentParser::ArgParser::PositionalMultiIntValue() {
    for (size_t i = 0; i < int_args.size(); ++i) {
        if (int_args[i].GetPositional() && int_args[i].GetMultiValue()) {
            if (int_args[i].GetValues().size() < int_args[i].GetMinArgsCount()) {
                return false;
            }
        }
        if (int_args[i].GetMultiValue()) {
            if (int_args[i].GetValues().size() < int_args[i].GetMinArgsCount()) {
                return false;
            }
        }
    }

    return true;
}

bool ArgumentParser::ArgParser::PositionalMultiStringValue() {
    for (size_t i = 0; i < string_args.size(); ++i) {
        if (string_args[i].GetPositional() && string_args[i].GetMultiValue() &&
        (string_args[i].GetValues().size() < string_args[i].GetMinArgsCount())) {
                return false;
        }
        if (string_args[i].GetMultiValue() &&
        (string_args[i].GetValues().size() < string_args[i].GetMinArgsCount())) {
            return false;
        }
    }

    return true;
}
