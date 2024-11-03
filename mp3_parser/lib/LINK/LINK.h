#pragma once

#include "../BasicFrame.h"

class LINK : public Frame {
public:
    explicit LINK(std::fstream& file);

    std::string Info() const override;

private:
    std::string frame_identifier_;
    std::string URL_;
    std::string additional_data_;
};
