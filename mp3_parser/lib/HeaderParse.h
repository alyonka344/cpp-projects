#pragma once

#include <fstream>

struct ExtendedHeader {
    uint32_t size;
    bool tag_is_an_update;
    bool CRC_data_present;
    bool tag_restrictions;
    std::string info_about_flags;
};

class Header {
public:
    explicit Header(std::fstream& file);

    ~Header() = default;

    uint32_t Size();

private:
    std::string identifier_;
    std::string version_;
    bool unsynchronisation_{};
    bool extended_header_{};
    bool experimental_indicator_{};
    bool footer_present_{};
    uint32_t size_{};
    ExtendedHeader extended_header_info_{};
};

