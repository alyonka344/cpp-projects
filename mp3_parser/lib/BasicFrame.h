#pragma once

#include "GeneralFunctions.h"

#include <fstream>
#include <iostream>


class Frame {
public:
    explicit Frame(std::fstream& file);

    Frame() = default;

    virtual ~Frame() = default;

    virtual std::string Info() const;

    friend std::ostream& operator<<(std::ostream& stream, const Frame& frame);

    Frame(const Frame& frame);

    uint32_t Size();

protected:
    std::string id_;
    uint32_t size_{};

private:
    bool tag_alter_preservation_{};
    bool file_alter_preservation_{};
    bool read_only_{};
    bool grouping_identity_{};
    bool compression_{};
    bool encryption_{};
    bool unsynchronisation_{};
    bool data_length_indicator_{};
};

const uint16_t kIDLength = 4;
const uint16_t kNumberOfUsedBit = 6;
const uint16_t kSizeOfChar = 1;
const uint16_t kLengthOfFrameSize = 4;
const uint16_t kTagAlterPreservationFlag = 6;
const uint16_t kFileAlterPreservationFlag = 5;
const uint16_t kPositionOfReadOnlyFlag = 4;
