#pragma once

#include "../BasicFrame.h"

#include <vector>

struct EventInfo {
    char type_of_event;
    uint32_t time_stamp;
};

class ETCO : public Frame {
public:
    explicit ETCO(std::fstream& file);

    std::string Info() const override;

private:
    char time_stamp_format_{};
    std::vector<EventInfo> events_;
};
