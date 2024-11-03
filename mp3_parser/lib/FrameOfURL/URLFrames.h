#pragma once

#include "..\BasicFrame.h"

class URLFrame : public Frame {
public:
    explicit URLFrame(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string URL_;
    std::string description_;
};
