#include "USLT.h"

const uint16_t kLengthOfLanguage = 3;

USLT::USLT(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadingToSize(file, language_, kLengthOfLanguage);
    ReadUpToNullCharacter(file, description_);
    ReadingToSize(file, language_, size_ - kLengthOfLanguage - kSizeOfChar - description_.length());
}

std::string USLT::Info() const {
    return Frame::Info() + "\nLanguage: " + language_ + "\nDescription: "
           + description_ + "\nText: " + text_;
}
