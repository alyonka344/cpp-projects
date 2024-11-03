#include "SYLT.h"

const uint16_t kLanguageLength = 3;
const uint16_t kSizeOfTimeStamp = 4;

SYLT::SYLT(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadingToSize(file, language_, kLanguageLength);
    file.read(&time_stamp_format_, kSizeOfChar);
    file.read(&content_type_, kSizeOfChar);
    ReadUpToNullCharacter(file, description_);

    for (int i = 0; i < size_ - 3 * kSizeOfChar - description_.length() - language_.length(); i += kSizeOfTimeStamp) {
        TextInfo current_string;
        ReadUpToNullCharacter(file, current_string.text);
        current_string.time_stamp = ReadingANumber(file, current_string.time_stamp);
        i += current_string.text.size();
        text_from_frame.push_back(current_string);
    }
}

std::string SYLT::Info() const {
    std::string string_for_output = Frame::Info() + "\nLanguage: " + language_;
    if (time_stamp_format_ == 1) {
        string_for_output += "\nAbsolute time, 32 bit sized, using MPEG frames as unit";
    } else {
        string_for_output += "\nAbsolute time, 32 bit sized, using milliseconds as unit";
    }

    string_for_output += "\nDescription: " + description_;

    for (const TextInfo& string: text_from_frame) {
        string_for_output += string.text;
        string_for_output += ", Time stamp: " + std::to_string(string.time_stamp);
    }

    return string_for_output;
}
