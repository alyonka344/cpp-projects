#pragma once

#include "../BasicFrame.h"

class POSS : public Frame {
public:
    explicit POSS(std::fstream& file);

    std::string Info() const override;

private:
    char time_stamp_format_{};
    uint32_t position_{};
};
