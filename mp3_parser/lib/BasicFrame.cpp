#include "BasicFrame.h"

const uint16_t kPositionOfGroupingIdentityFlag = 6;
const uint16_t kPositionOfCompressionFlag = 3;
const uint16_t kPositionOfEncryptionFlag = 2;
const uint16_t kPositionOfUnsynchronisationFlag = 1;
const uint16_t kPositionOfDataLengthIndicator = 0;

Frame::Frame(std::fstream& file) {
    file.seekg(-kIDLength, std::ios::cur);

    char symbol;
    for (int i = 0; i < kIDLength; ++i) {
        file.read(&symbol, kSizeOfChar);
        id_ += symbol;
    }

    for (int i = 0; i < kLengthOfFrameSize; i++) {
        file.read(&symbol, kSizeOfChar);
        for (int j = kNumberOfUsedBit; j >= 0; --j) {
            size_ <<= 1;
            if ((1 << j) & symbol) {
                size_ |= 1;
            }
        }
    }

    file.read(&symbol, kSizeOfChar);
    tag_alter_preservation_ = symbol & (1 << kTagAlterPreservationFlag);
    file_alter_preservation_ = symbol & (1 << kFileAlterPreservationFlag);
    read_only_ = symbol & (1 << kPositionOfReadOnlyFlag);

    file.read(&symbol, kSizeOfChar);
    grouping_identity_ = symbol & (1 << kPositionOfGroupingIdentityFlag);
    compression_ = symbol & (1 << kPositionOfCompressionFlag);
    encryption_ = symbol & (1 << kPositionOfEncryptionFlag);
    unsynchronisation_ = symbol & (1 << kPositionOfUnsynchronisationFlag);
    data_length_indicator_ = symbol & (1 << kPositionOfDataLengthIndicator);
}

std::string Frame::Info() const {
    return "ID: " + id_;
}

std::ostream& operator<<(std::ostream& stream, const Frame& frame) {
    return stream << frame.Info() << "\n\n";
}

uint32_t Frame::Size() {
    return size_;
}

Frame::Frame(const Frame& frame) {
    id_ = frame.id_;
    size_ = frame.size_;
}
