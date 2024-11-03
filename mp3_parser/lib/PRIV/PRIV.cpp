#include "PRIV.h"

PRIV::PRIV(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadUpToNullCharacter(file, owner_identifier_);
    ReadingToSize(file, the_private_data_, size_ - kSizeOfChar - owner_identifier_.length());
}

std::string PRIV::Info() const {
    return Frame::Info() + "\nOwner identifier: " + owner_identifier_ + "\nThe private data: " + the_private_data_;
}
