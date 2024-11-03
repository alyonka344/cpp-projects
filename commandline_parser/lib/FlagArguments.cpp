#include "FlagArguments.h"
#include "HelpArguments.h"

char FlagArguments::GetShortParam() const {
    return short_param_;
}

std::string FlagArguments::GetLongParam() {
    return long_param_;
}

bool FlagArguments::GetFlag() {
    return flag_;
}

std::string FlagArguments::GetDescription() {
    return description_;
}

bool FlagArguments::GetDefaultFlag() const {
    return default_flag;
}

void FlagArguments::SetFlag(bool flag) {
    *flag_ = flag;
}

void FlagArguments::Default(bool value) {
    default_flag = true;
    SetFlag(value);
}

void FlagArguments::StoreValue(bool &value) {
    flag_ = &value;
}
