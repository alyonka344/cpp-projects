#include "../BasicFrame.h"

class COMR : public Frame {
public:
    explicit COMR(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string price_string_;
    std::string valid_until_;
    std::string contact_URL_;
    char received_as_{};
    std::string name_of_seller_;
    std::string description_;
    std::string picture_MIME_type_;
    std::string seller_logo_;
};
