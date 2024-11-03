#include "PCNT.h"

PCNT::PCNT(std::fstream& file) : Frame(file) {
    counter_ = ReadingANumber(file, size_);
}

std::string PCNT::Info() const {
    return Frame::Info() + "\nPlay counter: " + std::to_string(counter_);
}
