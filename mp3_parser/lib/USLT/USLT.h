#pragma once

#include "../BasicFrame.h"

class USLT : public Frame {
public:
    explicit USLT(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string language_;
    std::string description_;
    std::string text_;
};
