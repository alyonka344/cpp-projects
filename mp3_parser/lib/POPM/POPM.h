#pragma once

#include "../BasicFrame.h"

class POPM : public Frame {
public:
    explicit POPM(std::fstream& file);

    std::string Info() const override;

private:
    std::string email_to_user_;
    char rating_{};
    uint64_t counter_{};
};
