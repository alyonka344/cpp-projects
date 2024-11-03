#pragma once

#include "COMR.h"

const uint16_t kLengthOfDate = 8;

COMR::COMR(std::fstream& file) : Frame(file) {
    file.read(&text_encoding_, 1);
    ReadUpToNullCharacter(file, price_string_);

    char symbol;
    for (int i = 0; i < kLengthOfDate; ++i) {
        file.read(&symbol, kSizeOfChar);
        valid_until_ += symbol;
        if (i == 3 || i == 5 || i == 7) {
            valid_until_ += '.';
        }
    }
    file.read(&symbol, kSizeOfChar);
    ReadUpToNullCharacter(file, contact_URL_);
    file.read(&received_as_, kSizeOfChar);
    ReadUpToNullCharacter(file, name_of_seller_);
    ReadUpToNullCharacter(file, description_);
    ReadUpToNullCharacter(file, picture_MIME_type_);
    ReadingToSize(file, seller_logo_, size_ - 2 * kSizeOfChar - price_string_.length() -
                                      valid_until_.length() - contact_URL_.length() - name_of_seller_.length() -
                                      description_.length() - picture_MIME_type_.length());
}

std::string COMR::Info() const {
    std::string string_for_output = Frame::Info() + "\nPrice string: " + price_string_ +
                         "\nValid until: " + valid_until_ + "\nContact URL: " + contact_URL_ + "\nReceived as: ";
    switch (received_as_) {
        case 0:
            string_for_output += "Other";
            break;
        case 1:
            string_for_output += "Standard CD album with other songs";
            break;
        case 2:
            string_for_output += "Compressed audio on CD";
            break;
        case 3:
            string_for_output += "File over the Internet";
            break;
        case 4:
            string_for_output += "Stream over the Internet";
            break;
        case 5:
            string_for_output += "As note sheets";
            break;
        case 6:
            string_for_output += "As note sheets in a book with other sheets";
            break;
        case 7:
            string_for_output += "Music on other media";
            break;
        case 8:
            string_for_output += "Non-musical merchandise";
            break;
    }
    string_for_output += "\nName of seller: " + name_of_seller_ +
                         "\nDescription: " + description_;

    if (picture_MIME_type_.length() != 0) {
        string_for_output += "\nPicture MIME type: " + picture_MIME_type_ +
                             "\nSeller logo: " + seller_logo_;
    } else if (seller_logo_.length() != 0) {
        string_for_output += "\nPicture MIME type: image/\nSeller logo: " + seller_logo_;
    }

    return string_for_output;
}
