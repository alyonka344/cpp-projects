#pragma once

#include <filesystem>
#include <istream>
#include <fstream>

#include "sections_and_values.h"


namespace omfl {

class ParserOMFL {
public:
    ParserOMFL() = default;
    bool valid() const;
    void SetValidation(bool validation);
    Section Get(const std::string& name_of_section) const;
    Section* GetCurrentSection();
    void SetCurrentSection(Section* current_section);

    std::vector<Section*> sections_{};
private:
    bool validation_ = true;
    Section* current_section_ = nullptr;
};

ParserOMFL parse(const std::filesystem::path& path);
ParserOMFL parse(const std::string& str);

}