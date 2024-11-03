#include "POPM.h"

POPM::POPM(std::fstream& file) : Frame(file) {
    ReadUpToNullCharacter(file, email_to_user_);
    file.read(&rating_, kSizeOfChar);
    counter_ = ReadingANumber(file, size_ - email_to_user_.length() - kSizeOfChar);
}

std::string POPM::Info() const {
    std::string string_for_output = Frame::Info() + "\nEmail to user: " + email_to_user_ +
                         "\nRating: " + std::to_string(static_cast<int32_t>(rating_) + 128);
    if (counter_ != 0) {
        string_for_output += "\nCounter: " + std::to_string(counter_);
    }

    return string_for_output;
}
