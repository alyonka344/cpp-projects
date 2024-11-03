#include "parser.h"

std::vector<std::string> ParseSection(const std::string& original_section) {
    std::vector<std::string> sections;
    std::string section = RemovingSpaces(original_section);
    std::string current_section;
    for (int i = 1; i < section.length() - 1; ++i) {
        if (section[i] != '.') {
            current_section += section[i];
        } else {
            sections.push_back(current_section);
            current_section = "";
        }
    }
    sections.push_back(current_section);
    return sections;
}

Section* FindSection(std::vector<Section*>& sections, const std::string& name_of_string) {
    for (int j = 0; j < sections.size(); ++j) {
        if ((sections)[j]->GetValue() == name_of_string) {
            return (sections)[j];
        }
    }
    return nullptr;
}

void CheckString(omfl::ParserOMFL& OMFL_string, const std::string &str) {
    if (RemovingSpaces(str).empty()) {
        return;
    }
    int64_t index_of_key = str.find('=');
    if (index_of_key == -1) {
        if (!ValidSection(str)) {
            OMFL_string.SetValidation(false);
            return;
        } else {
            std::vector<std::string> sections = ParseSection(str);
            std::vector<Section*>* section_to_add = &OMFL_string.sections_;
            for (int i = 0; i < sections.size(); ++i) {
                Section* found_section = FindSection(*section_to_add, sections[i]);
                if (found_section == nullptr) {
                    Section* new_section = new Section(sections[i]);
                    (*section_to_add).push_back(new_section);
                    section_to_add = &(new_section->subsections_);
                    OMFL_string.SetCurrentSection(new_section);
                } else {
                    OMFL_string.SetCurrentSection(found_section);
                    section_to_add = &(found_section->subsections_);
                }
            }
        }
    } else {
        std::string key = str.substr(0, index_of_key);
        std::string value = str.substr(index_of_key + 1);
        Section* new_section = new Section;
        if (!ValidKey(key)) {
            OMFL_string.SetValidation(false);
            return;
        }
        if (!ValidString(value) && !ValidRealNumber(value)
            && !ValidInteger(value) && !ValidArray(value) && !ValidBooleanVar(value)) {
            OMFL_string.SetValidation(false);
            return;
        }
        key = RemovingSpaces(key);
        value = RemovingSpaces(value);
        new_section->SetValue(key);
        Section* key_value = new Section(value);
        new_section->subsections_.push_back(key_value);
        if (OMFL_string.GetCurrentSection() != nullptr) {
            if (FindSection(OMFL_string.GetCurrentSection()->subsections_, key) != nullptr) {
                OMFL_string.SetValidation(false);
                return;
            }
            OMFL_string.GetCurrentSection()->subsections_.push_back(new_section);
        } else {
            if (FindSection(OMFL_string.sections_, key) != nullptr) {
                OMFL_string.SetValidation(false);
                return;
            }
            OMFL_string.sections_.push_back(new_section);
        }
    }
}

omfl::ParserOMFL omfl::parse(const std::string& str) {
    ParserOMFL* OMFL_string = new ParserOMFL();
    std::string string_to_parse;
    int ind = 0;
    int count_of_quotes = 0;
    int count_of_comments = 0;
    while (ind < str.length()) {
        if (str[ind] == '#' && count_of_quotes == 0) {
            count_of_comments++;
        } else if (str[ind] == '"') {
            if (count_of_quotes == 0) {
                count_of_quotes++;
            } else {
                count_of_quotes--;
            }
            string_to_parse += str[ind];
        } else if (str[ind] != '\n' && count_of_comments == 0) {
            string_to_parse += str[ind];
        } else if (str[ind] == '\n' && count_of_quotes == 0){
            CheckString(*OMFL_string, string_to_parse);
            string_to_parse = "";
            count_of_quotes = 0;
            count_of_comments = 0;
        }
        ind++;
    }
    CheckString(*OMFL_string, string_to_parse);
    return *OMFL_string;
}

omfl::ParserOMFL omfl::parse(const std::filesystem::path& path) {
    std::string string_from_file;
    std::string one_string;
    std::ifstream file(path.string());
    while (getline(file, one_string)) {
        string_from_file += one_string + '\n';
    }

    return parse(string_from_file);
}

bool omfl::ParserOMFL::valid() const{
    return validation_;
}

void omfl::ParserOMFL::SetValidation(bool validation) {
    validation_ = validation;
}

Section omfl::ParserOMFL::Get(const std::string& name_of_section) const{
    std::vector<std::string> sections;
    if (std::count(&name_of_section[0], &name_of_section[name_of_section.length()], '.') == 0) {
        sections.push_back(name_of_section);
    } else {
        std::string section = "[" + name_of_section + "]";
        sections = ParseSection(section);
    }
    std::vector<Section*> current_section = sections_;
    int ind;
    for (int i = 0; i < sections.size(); ++i) {
        ind = -1;
        for (int j = 0; j < current_section.size(); ++j) {
            if (current_section[j]->GetValue() == sections[i]) {
                ind = j;
                if (i != sections.size() - 1) {
                    current_section = current_section[j]->subsections_;
                }
            }
        }
    }

    if (ind == -1) {
        Section* to_return = new Section("");
        return *to_return;
    }
    return *current_section[ind];
}

Section* omfl::ParserOMFL::GetCurrentSection() {
    return current_section_;
}

void omfl::ParserOMFL::SetCurrentSection(Section* current_section) {
    current_section_ = current_section;
}
