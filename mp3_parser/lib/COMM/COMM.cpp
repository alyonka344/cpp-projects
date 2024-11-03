#pragma once

#include "COMM.h"

const uint16_t kLanguageLength = 3;

COMM::COMM(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadingToSize(file, language_, kLanguageLength);
    ReadUpToNullCharacter(file, description_);
    ReadingToSize(file, information_, size_ - kSizeOfChar - kLanguageLength - description_.length());
}

std::string COMM::Info() const {
    return Frame::Info() + "\nLanguage: " + language_ + "\nDescription: "
           + description_ + "\nInformation: " + information_;
}
