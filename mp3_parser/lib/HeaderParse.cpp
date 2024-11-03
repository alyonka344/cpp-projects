#include "HeaderParse.h"

const uint16_t kIdentifierLength = 3;
const uint16_t kSizeOfChar = 1;
const uint16_t kVersionLength = 2;
const uint16_t kPositionOfUnsynchronisationFlag = 7;
const uint16_t kPositionOfExtendedHeaderFlag = 6;
const uint16_t kPositionOfExperementalFlag = 5;
const uint16_t kPositionOfFooterFlag = 4;
const uint16_t kNumberOfBytesPerSize = 4;
const uint16_t kNumberOfUsedBit = 6;
const uint16_t kPositionOfTagIsAnUpdateFlag = 6;
const uint16_t kPositionOfCRCDataFlag = 5;
const uint16_t kPositionOfRestrictionsFlag = 4;

Header::Header(std::fstream& file) {
    char symbol;
    for (int i = 0; i < kIdentifierLength; ++i) {
        file.read(&symbol, kSizeOfChar);
        identifier_ += symbol;
    }

    for (int i = 0; i < kVersionLength; i++) {
        file.read(&symbol, kSizeOfChar);
        version_ += symbol;
    }

    file.read(&symbol, kSizeOfChar);
    unsynchronisation_ = symbol & (1 << kPositionOfUnsynchronisationFlag);
    extended_header_ = symbol & (1 << kPositionOfExtendedHeaderFlag);
    experimental_indicator_ = symbol & (1 << kPositionOfExperementalFlag);
    footer_present_ = symbol & (1 << kPositionOfFooterFlag);

    for (int i = 0; i < kNumberOfBytesPerSize; i++) {
        file.read(&symbol, kSizeOfChar);
        for (int j = kNumberOfUsedBit; j >= 0; --j) {
            size_ <<= 1;
            if ((1 << j) & symbol) {
                size_ |= 1;
            }
        }
    }

    if (extended_header_) {
        for (int i = 0; i < kNumberOfBytesPerSize; i++) {
            file.read(&symbol, kSizeOfChar);
            for (int j = kNumberOfUsedBit; j >= 0; --j) {
                extended_header_info_.size <<= 1;
                if ((1 << j) & symbol) {
                    extended_header_info_.size |= 1;
                }
            }
        }
        file.seekg(kSizeOfChar, std::ios_base::cur);

        file.read(&symbol, kSizeOfChar);
        extended_header_info_.tag_is_an_update = symbol & (1 << kPositionOfTagIsAnUpdateFlag);
        extended_header_info_.CRC_data_present = symbol & (1 << kPositionOfCRCDataFlag);
        extended_header_info_.tag_restrictions = symbol & (1 << kPositionOfRestrictionsFlag);

        for (int i = 0; i < extended_header_info_.size - 2 * kSizeOfChar - kNumberOfBytesPerSize; ++i) {
            file.read(&symbol, kSizeOfChar);
            extended_header_info_.info_about_flags += symbol;
        }
    }
}

uint32_t Header::Size() {
    return size_;
}
