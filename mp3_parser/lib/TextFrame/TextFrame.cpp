#include "TextFrame.h"

TextFrame::TextFrame(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    if (id_ == "TXXX") {
        ReadUpToNullCharacter(file, additional_information_);
    }
    ReadingToSize(file, information_, size_ - kSizeOfChar - additional_information_.length());
}

std::string TextFrame::Info() const {
    if (id_ == "TXXX") {
        return Frame::Info() + "\nDescription: " + additional_information_ + "\nInformation: " + information_;
    } else {
        return Frame::Info() + "\nInformation: " + information_;
    }
};