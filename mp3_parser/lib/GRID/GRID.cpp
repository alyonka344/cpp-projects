#include "GRID.h"

GRID::GRID(std::fstream& file) : Frame(file) {
    ReadUpToNullCharacter(file, owner_identifier_);
    file.read(&group_symbol_, kSizeOfChar);
    ReadingToSize(file, group_dependent_data_, size_ - kSizeOfChar - owner_identifier_.length());
}

std::string GRID::Info() const {
    std::string string_for_output = Frame::Info() + "\nOwner identifier: " + owner_identifier_ +
                         "\nMethod symbol: " + group_symbol_;
    if (!group_dependent_data_.empty()) {
        string_for_output += "\nEncryption data: " + group_dependent_data_;
    }

    return string_for_output;
}
