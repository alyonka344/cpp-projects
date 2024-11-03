#include "sections_and_values.h"

std::vector<std::string> SplitArray(std::string array) {
    std::vector<std::string> split_array;
    std::string val;
    int quotes = 0;
    int brackets = 0;
    for (int i = 1; i < array.length() - 1; ++i) {
        if (array[i] == ',' && quotes == 0 && brackets == 0) {
            val = RemovingSpaces(val);
            split_array.push_back(val);
            val = "";
        } else if (array[i] == '[') {
            brackets++;
            val += array[i];
        } else if (array[i] == ']') {
            brackets--;
            val += array[i];
        } else if (array[i] == '"') {
            if (quotes == 0) {
                quotes++;
                val += array[i];
            } else {
                quotes--;
                val += array[i];
            }
        } else {
            val += array[i];
        }
    }
    if (!val.empty()) {
        val = RemovingSpaces(val);
        split_array.push_back(val);;
    }
    return split_array;
}

bool Section::EmptySubsections() {
    if (subsections_.empty()) {
        return true;
    } else {
        return false;
    }
}

Section& Section::operator[](int index) {
    std::vector<std::string> split_array = SplitArray(subsections_[0]->value_);
    std::string value;
    if (index > split_array.size() - 1) {
        value = "error";
    } else {
        value = split_array[index];
    }
    Section* array_element = new Section(value);
    Section* array_to_return = new Section;
    array_to_return->subsections_.push_back(array_element);
    return *array_to_return;
}

Section Section::Get(const std::string& name_of_section) const {
    for (int i = 0; i < subsections_.size(); ++i) {
        if (subsections_[i]->GetValue() == name_of_section) {
            return *subsections_[i];
        }
    }
    Section error("error");
    return error;
}

int Section::AsInt() {
    return std::stoi(subsections_[0]->value_);
}

void Section::SetValue(const std::string& value) {
    value_ = value;
}

std::string Section::GetValue() {
    return value_;
}

bool Section::IsInt() {
    if (EmptySubsections()) {
        return false;
    } else {
        return ValidInteger(subsections_[0]->value_);
    }
}

float Section::AsFloat() {
    return std::stof(subsections_[0]->value_);
}

bool Section::IsFloat() {
    if (EmptySubsections()) {
        return false;
    } else {
        return ValidRealNumber(subsections_[0]->value_);
    }
}

std::string Section::AsString() {
    return subsections_[0]->value_.substr(1, subsections_[0]->value_.length() - 2);
}

bool Section::IsString() {
    if (EmptySubsections()) {
        return false;
    } else {
        return ValidString(subsections_[0]->value_);
    }
}

int Section::AsIntOrDefault(int default_number) {
    if (IsInt()) {
        return AsInt();
    } else {
        return default_number;
    }
}

float Section::AsFloatOrDefault(float default_number) {
    if (IsFloat()) {
        return AsFloat();
    } else {
        return default_number;
    }
}

std::string Section::AsStringOrDefault(std::string default_string) {
    if (IsString()) {
        return AsString();
    } else {
        return default_string;
    }
}

bool Section::IsBool() {
    if (EmptySubsections()) {
        return false;
    } else {
        return ValidBooleanVar(subsections_[0]->value_);
    }
}

bool Section::AsBool() {
    if (subsections_[0]->value_ == "true") {
        return true;
    } else {
        return false;
    }
}

bool Section::AsBoolOrDefault(bool default_bool_var) {
    if (IsBool()) {
        return AsBool();
    } else {
        return default_bool_var;
    }
}

bool Section::IsArray() {
    if (EmptySubsections()) {
        return false;
    } else {
        return ValidArray(subsections_[0]->value_);
    }
}

