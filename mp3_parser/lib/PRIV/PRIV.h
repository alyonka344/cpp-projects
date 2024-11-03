#pragma once

#include "..\BasicFrame.h"

class PRIV : public Frame {
public:
    explicit PRIV(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string the_private_data_;
    std::string owner_identifier_;
};
