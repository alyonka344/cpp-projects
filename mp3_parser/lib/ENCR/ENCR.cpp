#include "ENCR.h"

ENCR::ENCR(std::fstream& file) : Frame(file) {
    ReadUpToNullCharacter(file, owner_identifier_);
    file.read(&method_symbol_, kSizeOfChar);
    ReadingToSize(file, encryption_data_, size_ - kSizeOfChar - owner_identifier_.length());
}

std::string ENCR::Info() const {
    std::string string_for_output = Frame::Info() + "\nOwner identifier: " + owner_identifier_ +
                         "\nMethod symbol: " + method_symbol_;
    if (!encryption_data_.empty()) {
        string_for_output += "\nEncryption data: " + encryption_data_;
    }

    return string_for_output;
}
