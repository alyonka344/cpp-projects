#pragma once

#include "../BasicFrame.h"

class ENCR : public Frame {
public:
    explicit ENCR(std::fstream& file);

    std::string Info() const override;

private:
    char method_symbol_{};
    std::string encryption_data_;
    std::string owner_identifier_;
};
