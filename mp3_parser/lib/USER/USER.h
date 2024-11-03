#pragma once

#include "../BasicFrame.h"

class USER : public Frame {
public:
    explicit USER(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_;
    std::string language_;
    std::string the_actual_text_;
};
