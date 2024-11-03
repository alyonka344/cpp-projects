#include "LINK.h"

LINK::LINK(std::fstream& file) : Frame(file) {
    ReadingToSize(file, frame_identifier_, kIDLength);
    ReadUpToNullCharacter(file, URL_);
    ReadingToSize(file, additional_data_, size_ - kIDLength - URL_.length());
}

std::string LINK::Info() const {
    std::string string_for_output = Frame::Info() + "\nFrame identifier: " + frame_identifier_ + "\nURL: " + URL_;
    if (!additional_data_.empty()) {
        string_for_output += "\nAdditional data: " + additional_data_;
    }

    return string_for_output;
}
