#include "SEEK.h"

SEEK::SEEK(std::fstream& file) : Frame(file) {
    offset_ = ReadingANumber(file, size_);
}

std::string SEEK::Info() const {
    return Frame::Info() + "\nMinimum offset to next tag: " + std::to_string(offset_);
}
