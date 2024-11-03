#include "HammingCode.h"
#include <vector>

std::string ConversionStringToBits(std::string word) {
    std::string word_in_bits;
    for (int i = 0; i < word.length(); ++i) {
        std::bitset<8> letter = word[i];
        word_in_bits += letter.to_string();
    }

    return word_in_bits;
}

std::string ConversionStringToBytes(std::string word_in_bits) {
    std::string word;
    std::bitset<8> letter;
    for (int i = 0; i < word_in_bits.length(); ++i) {
        letter[7 - i % 8] = word_in_bits[i] - '0';
        if (i % 8 == 7) {
            uint64_t int_letter = letter.to_ulong();
            word += static_cast<char>(int_letter);
        }
    }
    return word;
}

std::string FileCoding(std::string uncoded_word) {

    uint32_t size_of_uncoded_word = 0;
    uint32_t size_of_coded_word = 0;
    std::string coded_word;

    while (size_of_uncoded_word < uncoded_word.length()) {
        if (!((size_of_coded_word + 1) & (size_of_coded_word))) {
            coded_word += "0";
        } else {
            coded_word += uncoded_word[size_of_uncoded_word];
            size_of_uncoded_word++;
        }
        size_of_coded_word++;
    }

    for (int i = 1; i < size_of_coded_word + 1; i *= 2) {
        uint32_t count_of_ones = 0;
        for (int j = i; j < size_of_coded_word + 1; j += 2 * i) {
            for (int k = 0; k < i && (k + j) < size_of_coded_word + 1; k++) {
                count_of_ones += (coded_word[j + k - 1] - '0');
            }
        }
        coded_word[i - 1] = static_cast<char>('0' + (count_of_ones % 2));
    }

    return coded_word;
}

std::string FileDecoding(std::string& coded_word) {
    std::string uncoded_word;

    uint32_t false_control_bits = 0;
    for (int i = 1; i < coded_word.length() + 1; i *= 2) {
        uint32_t count_of_ones = (coded_word[i - 1] - '0');
        for (int j = i; j < coded_word.length() + 1; j += 2 * i) {
            for (int k = 0; k < i && (k + j) < coded_word.length() + 1; k++) {
                if ((k + j) & (k + j - 1)) {
                    count_of_ones += (coded_word[j + k - 1] - '0');
                }
            }
        }
        if ((count_of_ones % 2) != 0) {
            false_control_bits += i;
        }
    }

    for (int i = 0; i < coded_word.length(); i++) {
        if (!((i + 1) & i)) {
            continue;
        } else if (i == false_control_bits - 1) {
            if (coded_word[i] == '0') {
                uncoded_word += '1';
            } else {
                uncoded_word += '0';
            }
        } else {
            uncoded_word += coded_word[i];
        }
    }

    return uncoded_word;
}
