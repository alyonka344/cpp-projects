#include "..\BasicFrame.h"

class COMM : public Frame {
public:
    explicit COMM(std::fstream& file);

    std::string Info() const override;

private:
    char text_encoding_{};
    std::string language_;
    std::string description_;
    std::string information_;
};
