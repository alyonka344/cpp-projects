#pragma once

#include "../BasicFrame.h"

class UFID : public Frame {
public:
    explicit UFID(std::fstream& file);

    std::string Info() const override;

private:
    std::string owner_identifier_;
    std::string identifier_;
};
