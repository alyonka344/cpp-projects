#pragma once

#include "../BasicFrame.h"

#include <vector>

struct TextInfo {
    std::string text;
    uint32_t time_stamp;
};

class SYLT : public Frame {
public:
    explicit SYLT(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string language_;
    char time_stamp_format_;
    char content_type_;
    std::string description_;
    std::vector<TextInfo> text_from_frame;
};
