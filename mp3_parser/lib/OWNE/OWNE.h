#pragma once

#include "../BasicFrame.h"

class OWNE : public Frame {
public:
    explicit OWNE(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string seller_;
    std::string price_paid_;
    std::string date_of_purch_;
};
