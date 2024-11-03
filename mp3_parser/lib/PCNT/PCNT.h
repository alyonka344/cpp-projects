#pragma once

#include "../BasicFrame.h"

class PCNT : public Frame {
public:
    explicit PCNT(std::fstream& file);

    std::string Info() const override;

private:
    uint64_t counter_{};
};
