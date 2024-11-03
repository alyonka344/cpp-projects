#pragma once

#include "..\BasicFrame.h"

class TextFrame : public Frame {
public:
    explicit TextFrame(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string information_;
    std::string additional_information_;
};