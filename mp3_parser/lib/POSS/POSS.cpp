#include "POSS.h"

POSS::POSS(std::fstream& file) : Frame(file) {
    file.read(&time_stamp_format_, kSizeOfChar);
    position_ = ReadingANumber(file, size_ - kSizeOfChar);
}

std::string POSS::Info() const {
    std::string string_for_output = Frame::Info();
    if (time_stamp_format_ == 1) {
        string_for_output += "\nAbsolute time, 32 bit sized, using MPEG frames as unit";
    } else {
        string_for_output += "\nAbsolute time, 32 bit sized, using milliseconds as unit";
    }
    string_for_output += "\nPosition: " + std::to_string(position_);

    return string_for_output;
}
