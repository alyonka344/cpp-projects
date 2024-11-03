#include "GeneralFunctions.h"

const uint16_t kSizeOfChar = 1;

void ReadUpToNullCharacter(std::fstream& file, std::string& variable) {
    char symbol;
    file.read(&symbol, kSizeOfChar);
    while (symbol != '\0') {
        variable += symbol;
        file.read(&symbol, kSizeOfChar);
    }
    variable += symbol;
}

void ReadingToSize(std::fstream& file, std::string& variable, uint32_t size) {
    char symbol;
    for (int i = 0; i < size; ++i) {
        file.read(&symbol, kSizeOfChar);
        variable += symbol;
    }
}

uint64_t ReadingANumber(std::fstream& file, uint32_t size) {
    uint64_t number_to_return = 0;
    char symbol;
    for (int i = 0; i < size; ++i) {
        file.read(&symbol, kSizeOfChar);
        for (int j = 7; j >= 0; --j) {
            number_to_return <<= 1;
            if ((1 << j) & symbol) {
                number_to_return |= 1;
            }
        }
    }
    return number_to_return;
}
