#include "USER.h"

const uint16_t kLengthLanguage = 3;

USER::USER(std::fstream& file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadingToSize(file, language_, kLengthLanguage);
    ReadingToSize(file, the_actual_text_, size_ - language_.length() - kSizeOfChar);
}

std::string USER::Info() const {
    return Frame::Info() + "\nLanguage: " + language_ + "\nThe actual text: " + the_actual_text_;
}
