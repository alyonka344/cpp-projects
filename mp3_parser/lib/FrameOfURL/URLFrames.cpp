#include "URLFrames.h"

URLFrame::URLFrame(std::fstream& file) : Frame(file) {
    uint8_t is_wxxx_frame = 0;
    if (id_ == "WXXX") {
        is_wxxx_frame = 1;
        file.read(&text_encoding_, kSizeOfChar);
        ReadUpToNullCharacter(file, description_);
    }
    ReadingToSize(file, URL_, size_ - is_wxxx_frame - description_.length());
}

std::string URLFrame::Info() const {
    if (id_ == "WXXX") {
        return Frame::Info() + "\nDescription: " + description_ + "\nURL: " + URL_;
    } else {
        return Frame::Info() + "\nURL: " + URL_;
    }
}
