#include "RBUF.h"

const uint16_t kLengthOfBufferSize = 3;

RBUF::RBUF(std::fstream& file) : Frame(file) {
    buffer_size_ = ReadingANumber(file, kLengthOfBufferSize);
    file.read(&embedded_info_flag_, kSizeOfChar);
    offset_ = ReadingANumber(file, size_ - kSizeOfChar - kLengthOfBufferSize);
}

std::string RBUF::Info() const {
    std::string string_for_output = Frame::Info() + "\nBuffer size: " + std::to_string(buffer_size_);
    if (embedded_info_flag_ | 1) {
        string_for_output += "\nTag may occur in the audio stream";
    }

    if (offset_ != 0) {
        string_for_output += "\nOffset to next tag: " + std::to_string(offset_);
    }

    return string_for_output;
}
