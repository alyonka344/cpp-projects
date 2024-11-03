#include "HelpArguments.h"

char HelpArguments::GetShortParam() const {
    return short_param_;
}

std::string HelpArguments::GetLongParam() {
    return long_param_;
}

std::string HelpArguments::GetDescription() {
    return description_;
}
