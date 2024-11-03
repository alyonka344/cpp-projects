#include "OWNE.h"

const uint16_t kLengthOfDate = 8;

OWNE::OWNE(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, kSizeOfChar);
    ReadUpToNullCharacter(file, price_paid_);

    char symbol;
    for (int i = 0; i < kLengthOfDate; ++i) {
        file.read(&symbol, kSizeOfChar);
        date_of_purch_ += symbol;
        if (i == 3 || i == 5 || i == 7) {
            date_of_purch_ += '.';
        }
    }

    ReadingToSize(file, seller_, size_ - kSizeOfChar - kLengthOfDate - price_paid_.length());
}

std::string OWNE::Info() const {
    return Frame::Info() + "\nPrice paid: " + price_paid_ + "\nDate of purch: " + date_of_purch_
           + "\nSeller: " + seller_;
}
