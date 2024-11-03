#include "check_on_valid.h"

#include <algorithm>
#include <stack>

std::string RemovingSpaces(const std::string& str) {
    std::string val;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ' || !val.empty()) {
            val += str[i];
        }
    }
    uint64_t index = val.length();
    for (int64_t i = val.length() - 1; i >= 0; --i) {
        if (val[i] != ' ') {
            break;
        } else {
            index = i;
        }
    }
    return val.substr(0, index);
}

bool ValidKey(const std::string& key) {
    std::string key_to_check = RemovingSpaces(key);
    if (key_to_check.length() == 0) {
        return false;
    }
    for (int i = 0; i < key_to_check.length(); ++i) {
        if ((key_to_check[i] < '0' && key_to_check[i] != '-') ||
        (key_to_check[i] > '9' && key_to_check[i] < 'A') ||
        (key_to_check[i] > 'Z' && key_to_check[i] < 'a' && key_to_check[i] != '_') ||
        key_to_check[i] > 'z') {
            return false;
        }
    }
    return true;
}

bool ValidInteger(const std::string& number) {
    std::string int_to_check = RemovingSpaces(number);
    if (int_to_check.length() == 0 || (int_to_check.length() == 1 &&
    (int_to_check[0] < '0' || int_to_check[0] > '9'))) {
        return false;
    }
    int index = (int_to_check[0] == '+' || int_to_check[0] == '-') ? 1: 0;
    while (index < int_to_check.length()) {
        if (int_to_check[index] < '0' || int_to_check[index] > '9') {
            return false;
        }
        index++;
    }
    return true;
}

bool ValidRealNumber(const std::string& number) {
    std::string float_to_check = RemovingSpaces(number);

    if (float_to_check.length() < 3) {
        return false;
    }
    if (std::count(&float_to_check[0], &float_to_check[float_to_check.length()], '.') != 1) {
        return false;
    }
    int64_t point_position = float_to_check.find('.');
    int index = (float_to_check[0] == '+' || float_to_check[0] == '-') ? 1: 0;
    if (point_position == float_to_check.length() - 1 || point_position == index) {
        return false;
    }

    while (index < point_position) {
        if (float_to_check[index] < '0' || float_to_check[index] > '9') {
            return false;
        }
        index++;
    }
    index++;
    while (index < float_to_check.length()) {
        if (float_to_check[index] < '0' || float_to_check[index] > '9') {
            return false;
        }
        index++;
    }

    return true;
}

bool ValidString(const std::string& string) {
    std::string string_to_check = RemovingSpaces(string);
    int64_t count_quotes = std::count(&string_to_check[0], &string_to_check[string_to_check.length()], '"');

    if (count_quotes == 2 && string_to_check[0] == '"' && string_to_check[string_to_check.length() - 1] == '"') {
        return true;
    }
    return false;
}

bool ValidBooleanVar(const std::string& bool_var) {
    std::string bool_to_check = RemovingSpaces(bool_var);
    if (bool_to_check == "true" || bool_to_check == "false") {
        return true;
    }
    return false;
}

bool CheckValidOfVal(const std::string& val) {
    return ValidBooleanVar(val) || ValidString(val)
    || ValidInteger(val) || ValidRealNumber(val);
}

bool ValidArray(const std::string& array) {
    std::string array_to_check = RemovingSpaces(array);
    if (array_to_check.length() < 2) {
        return false;
    }
    if (array_to_check[0] != '[' || array_to_check[array_to_check.length() - 1] != ']') {
        return false;
    }
    std::stack<char> brackets;
    int quotes = 0;
    for (int i = 0; i < array_to_check.length(); i++) {
        if (array_to_check[i] == ']' && quotes == 0) {
            if (brackets.top() != '[' || brackets.empty()) {
                return false;
            } else{
                brackets.pop();
            }
        } else if (array_to_check[i] == '[' && quotes == 0){
            brackets.push('[');
        } else if (array_to_check[i] == '"') {
            if (quotes == 0) {
                quotes++;
            } else {
                quotes--;
            }
        }
    }
    if (!brackets.empty() || quotes != 0) {
        return false;
    }

    std::string val;
    bool flag = true;
    for (int i = 0; i < array_to_check.length(); ++i) {
        if (array_to_check[i] == ',' && quotes == 0) {
            flag = flag && CheckValidOfVal(val);
            val = "";
        } else if (array_to_check[i] == '"') {
            if (quotes == 0) {
                quotes++;
                val += array_to_check[i];
            } else {
                quotes--;
                val += array_to_check[i];
            }
        } else if ((array_to_check[i] != ']' && array_to_check[i] != '[' && array_to_check[i] != '"'
        && quotes == 0) || quotes != 0) {
            val += array_to_check[i];
        }
    }
    if (!val.empty()) {
        flag = flag && CheckValidOfVal(val);
    }

    return flag;
}

bool ValidSection(const std::string& section) {
    std::string section_to_check = RemovingSpaces(section);
    if (section_to_check.length() <= 2) {
        return false;
    }
    if (section_to_check[0] != '[' || section_to_check[section_to_check.length() - 1] != ']'
    || section_to_check[1] == '.' || section_to_check[section_to_check.length() - 2] == '.') {
        return false;
    }
    for (int i = 1; i < section_to_check.length() - 2; ++i) {
        if (((section_to_check[i] < '0' && section_to_check[i] != '-' && section_to_check[i] != '.') ||
             (section_to_check[i] > '9' && section_to_check[i] < 'A') ||
             (section_to_check[i] > 'Z' && section_to_check[i] < 'a' && section_to_check[i] != '_') ||
             section_to_check[i] > 'z')) {
            return false;
        }
        if (section_to_check[i - 1] == '.' && section_to_check[i] == '.') {
            return false;
        }
    }
    return true;
}