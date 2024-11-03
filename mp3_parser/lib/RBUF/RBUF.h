#pragma once

#include "../BasicFrame.h"

class RBUF : public Frame {
public:
    explicit RBUF(std::fstream& file);

    std::string Info() const override;

private:
    uint32_t buffer_size_{};
    char embedded_info_flag_{};
    uint32_t offset_{};
};
