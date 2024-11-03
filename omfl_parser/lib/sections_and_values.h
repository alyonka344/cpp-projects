#include <iostream>
#include <vector>
#include "check_on_valid.h"

class Section {
public:
    Section(const std::string& value) {
        value_ = value;
    }
    Section() = default;

    Section& operator[](int index);

    bool EmptySubsections();
    Section Get(const std::string& name_of_section) const;
    int AsInt();
    bool IsInt();
    int AsIntOrDefault(int default_number);
    float AsFloat();
    bool IsFloat();
    float AsFloatOrDefault(float default_number);
    std::string AsString();
    bool IsString();
    std::string AsStringOrDefault(std::string default_string);
    bool IsBool();
    bool AsBool();
    bool AsBoolOrDefault(bool default_bool_var);
    bool IsArray();

    void SetValue(const std::string& value);
    std::string GetValue();

    std::vector<Section*> subsections_{};
private:
    std::string value_;
};
