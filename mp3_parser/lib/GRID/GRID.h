#pragma once

#include "../BasicFrame.h"

class GRID : public Frame {
public:
    explicit GRID(std::fstream& file);

    std::string Info() const override;

private:
    char group_symbol_{};
    std::string group_dependent_data_;
    std::string owner_identifier_;
};
