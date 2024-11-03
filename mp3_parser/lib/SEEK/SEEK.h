#pragma once

#include "../BasicFrame.h"

class SEEK : public Frame {
public:
    explicit SEEK(std::fstream& file);

    std::string Info() const override;

private:
    uint32_t offset_{};
};
