#include "UFID.h"

UFID::UFID(std::fstream& file) : Frame(file) {
    ReadUpToNullCharacter(file, owner_identifier_);
    ReadingToSize(file, identifier_, size_ - owner_identifier_.length());
}

std::string UFID::Info() const {
    return Frame::Info() + "\nOwner identifier: " + owner_identifier_ + "\nIdentifier: " + identifier_;
}
