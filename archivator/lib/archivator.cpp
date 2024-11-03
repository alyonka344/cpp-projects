#include "archivator.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <cstdio>

const uint8_t kMaxSizeOfFileName = 8;
const uint8_t kMaxSizeOfFile = 32;
const uint8_t kMaxOfWordSize = 16;
const uint8_t kSizeOfChar = 1;
const uint8_t kBitInByte = 8;
//const uint8_t kPasswordLength = 20;

std::string NameOfFile(const std::string& path) {
    std::string name;
    if (std::count(path.begin(), path.end(), '\\') == 0 &&
    std::count(path.begin(), path.end(), '/') == 0) {
        return path;
    } else {
        uint64_t i = path.length() - 1;
        while (path[i] != '\\' && path[i] != '/') {
            name = path[i] + name;
            i--;
        }
    }
    return name;
}

uint32_t SizeOfFile(const std::string& file_name) {
    std::ifstream file(file_name, std::ifstream::binary);
    file.seekg(0, std::ios_base::end);
    uint32_t size = file.tellg();
    file.seekg(0, std::ios_base::beg);
    file.close();
    return size;
}

uint32_t LengthOfCodedWord(uint32_t length_of_uncoded_word) {
    int i = 0;
    uint32_t length_of_coded_word = 0;
    while (i < length_of_uncoded_word) {
        length_of_coded_word++;
        if ((length_of_coded_word) & (length_of_coded_word - 1)) {
            i++;
        }
    }
    return length_of_coded_word;
}

void SetPassword(const std::string& archive_name, const std::string& password_to_set, const std::string& enter_password) {
    uint32_t end_of_file = SizeOfFile(archive_name  + ".haf");
    std::ifstream old_archive(archive_name + ".haf", std::ios_base::binary);

    char symbol;
    old_archive.read(&symbol, kSizeOfChar);
    int password_length = symbol + '0';
    std::string password;
    for (int i = 0; i < password_length; ++i) {
        old_archive.read(&symbol, kSizeOfChar);
        password += symbol;
    }

    if (enter_password != password) {
        std::cout << "wrong password or no password entered" << '\n';
        return;
    }

    std::ofstream new_archive(archive_name + "2.haf", std::ios_base::binary);
    if (password_to_set.length() >= 8 && password_to_set.length() <= 20) {
        char length = password_to_set.length() - '0';
        new_archive.write(&length, kSizeOfChar);
        for (int i = 0; i < password_to_set.length(); ++i) {
            new_archive.write(&password_to_set[i], kSizeOfChar);
        }
        std::cout << "password set" << '\n';
    } else {
        char length = 0 - '0';
        new_archive.write(&length, kSizeOfChar);
        std::cout << "no password or the password format is incorrect" << '\n';
    }
    while(old_archive.tellg() < end_of_file) {
        old_archive.read(&symbol, kSizeOfChar);
        new_archive.write(&symbol, kSizeOfChar);
    }
    old_archive.close();
    new_archive.close();
    std::remove((archive_name + ".haf").c_str());
    std::string old_name = archive_name + "2.haf";
    std::string new_name = archive_name + ".haf";
    std::rename(old_name.c_str(), new_name.c_str());
}

void CreateArchive(const std::string& archive_name, std::vector<std::string> files, uint16_t word_size, const std::string& password) {
    std::ofstream archive(archive_name + ".haf", std::ios_base::binary);
    if (password.length() >= 8 && password.length() <= 20) {
        char length = password.length() - '0';
        archive.write(&length, kSizeOfChar);
        for (int i = 0; i < password.length(); ++i) {
            archive.write(&password[i], kSizeOfChar);
        }
        std::cout << "password set" << '\n';
    } else {
        char length = 0 - '0';
        archive.write(&length, kSizeOfChar);
        std::cout << "no password or the password format is incorrect" << '\n';
    }
    archive.close();
    for (int i = 0; i < files.size(); i++) {
        Append(archive_name, files[i], word_size, password);
    }
    std::cout << "archive \"" << archive_name << "\" created" << '\n';
}

void ExtractFiles(const std::string& archive_name,  std::vector<std::string> files, const std::string& enter_password) {
    std::ifstream archive(archive_name + ".haf", std::ifstream::binary);
    if (!archive.is_open()) {
        std::cout << "archive doesn't exist";
        return;
    }
    char symbol;
    archive.read(&symbol, kSizeOfChar);
    int password_length = symbol + '0';
    std::string password;
    for (int i = 0; i < password_length; ++i) {
        archive.read(&symbol, kSizeOfChar);
        password += symbol;
    }

    if (enter_password != password) {
        std::cout << "wrong password or no password entered" << '\n';
        return;
    }

    uint32_t end_of_file = SizeOfFile(archive_name  + ".haf");

    std::bitset<kBitInByte> byte = 0;
    while(archive.tellg() < end_of_file) {
        std::string file_name;
        std::string string_from_file;
        int64_t length_of_string = 0;
        uint16_t word_size = 0;
        uint8_t size_file_name;
        uint32_t size_file;

        std::string coded_word_size;
        while (length_of_string < LengthOfCodedWord(kMaxOfWordSize)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_word_size = string_from_file.substr(0, LengthOfCodedWord(kMaxOfWordSize));
        std::string uncoded_word_size = FileDecoding(coded_word_size);
        std::bitset<kMaxOfWordSize> word_size_in_bits = 0;
        for (char k = 0; k < kMaxOfWordSize; ++k) {
            if (uncoded_word_size[k] == '1') {
                word_size_in_bits |= (1 << (15 - k));
            }
        }
        word_size = word_size_in_bits.to_ulong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxOfWordSize));
        length_of_string -= LengthOfCodedWord(kMaxOfWordSize);

        std::string coded_size_file_name;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFileName)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kMaxSizeOfFileName;
        }
        coded_size_file_name = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFileName));
        std::string uncoded_size_file_name = ConversionStringToBytes(FileDecoding(coded_size_file_name));
        size_file_name = static_cast<uint8_t>(uncoded_size_file_name[0]);
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFileName));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFileName);

        std::string coded_file_name;
        while (length_of_string < LengthOfCodedWord(size_file_name * kBitInByte)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_file_name = string_from_file.substr(0, LengthOfCodedWord(size_file_name * kBitInByte));
        file_name = ConversionStringToBytes(FileDecoding(coded_file_name));
        string_from_file = string_from_file.substr(LengthOfCodedWord(size_file_name * kBitInByte));
        length_of_string -= LengthOfCodedWord(size_file_name * kBitInByte);

        std::string coded_size_file;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFile)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_size_file = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFile));
        std::string uncoded_size_file = FileDecoding(coded_size_file);
        std::bitset<kMaxSizeOfFile> size_file_in_bits;
        for (char k = 0; k < kMaxSizeOfFile; ++k) {
            if (uncoded_size_file[k] == '1') {
                size_file_in_bits |= (1 << (31 - k));
            }
        }
        size_file = size_file_in_bits.to_ullong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFile));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFile);


        int64_t length_of_coded_file = (size_file / word_size) * LengthOfCodedWord(kBitInByte * word_size) +
                                   LengthOfCodedWord((size_file % word_size) * kBitInByte);

        if (!files.empty()) {
            bool flag = false;
            for (int i = 0; i < files.size(); ++i) {
                if (file_name == files[i])
                    flag = true;
            }
            if (flag) {
                std::filesystem::create_directory(archive_name);
                std::string path;
                path += archive_name;
                path += '/';
                path += file_name;
                std::ofstream file(path, std::ofstream::binary);
                std::string coded_word;

                int64_t i = 0;
                while (length_of_string < length_of_coded_file) {
                    archive.read(&symbol, kSizeOfChar);
                    byte = symbol;
                    string_from_file += byte.to_string();
                    length_of_string += kBitInByte;

                    if (length_of_string >= LengthOfCodedWord(word_size * kBitInByte) * (1 + i)) {
                        coded_word = string_from_file.substr(0, LengthOfCodedWord(word_size * kBitInByte));
                        std::string uncoded_word = ConversionStringToBytes(FileDecoding(coded_word));
                        for (int j = 0; j < word_size; ++j) {
                            file.write(&uncoded_word[j], kSizeOfChar);
                        }
                        string_from_file = string_from_file.substr(LengthOfCodedWord(word_size * kBitInByte));
                        i++;
                    }
                }
                length_of_string -= LengthOfCodedWord(word_size * kBitInByte) * (i - 1);
                if (length_of_string != 0) {
                    coded_word = string_from_file.substr(0, length_of_coded_file % LengthOfCodedWord(word_size * 8));
                    std::string uncoded_word = ConversionStringToBytes(FileDecoding(string_from_file));
                    for (int j = 0; j < uncoded_word.length(); ++j) {
                        file.write(&uncoded_word[j], kSizeOfChar);
                    }
                }
                file.close();
            } else {
                int64_t skip = ceil(static_cast<double> (length_of_coded_file - length_of_string) / 8.0);
                archive.seekg(skip, std::ios_base::cur);
            }
        } else {
            std::filesystem::create_directory(archive_name);
            std::string path;
            path += archive_name;
            path += '/';
            path += file_name;
            std::ofstream file(path, std::ofstream::binary);
            std::string coded_word;

            int64_t i = 0;
            while (length_of_string < length_of_coded_file) {
                archive.read(&symbol, kSizeOfChar);
                byte = symbol;
                string_from_file += byte.to_string();
                length_of_string += kBitInByte;

                if (length_of_string >= LengthOfCodedWord(word_size * kBitInByte) * (1 + i)) {
                    coded_word = string_from_file.substr(0, LengthOfCodedWord(word_size * kBitInByte));
                    std::string uncoded_word = ConversionStringToBytes(FileDecoding(coded_word));
                    for (int j = 0; j < word_size; ++j) {
                        file.write(&uncoded_word[j], kSizeOfChar);
                    }
                    string_from_file = string_from_file.substr(LengthOfCodedWord(word_size * kBitInByte));
                    i++;
                }
            }
            length_of_string -= LengthOfCodedWord(word_size * kBitInByte) * i;
            if (length_of_string != 0) {
                coded_word = string_from_file.substr(0, length_of_coded_file % LengthOfCodedWord(word_size * kBitInByte));
                std::string uncoded_word = ConversionStringToBytes(FileDecoding(string_from_file));
                for (int j = 0; j < uncoded_word.length(); ++j) {
                    file.write(&uncoded_word[j], kSizeOfChar);
                }
                length_of_string -= length_of_coded_file % LengthOfCodedWord(word_size * kBitInByte);
                string_from_file = string_from_file.substr(length_of_coded_file % LengthOfCodedWord(word_size * kBitInByte));
            }
            file.close();
        }
    }
    archive.close();
}

void List(const std::string& archive_name, const std::string& enter_password) {
    std::ifstream archive(archive_name  + ".haf", std::ifstream::binary);
    if (!archive.is_open()) {
        std::cout << "archive doesn't exist";
        return;
    }
    char symbol;
    archive.read(&symbol, kSizeOfChar);
    int password_length = symbol + '0';
    std::string password;
    for (int i = 0; i < password_length; ++i) {
        archive.read(&symbol, kSizeOfChar);
        password += symbol;
    }

    if (enter_password != password) {
        std::cout << "wrong password or no password entered" << '\n';
        return;
    }

    std::string file_name;
    std::string string_from_file;
    int64_t length_of_string = 0;

    uint32_t end_of_file = SizeOfFile(archive_name  + ".haf");

    std::bitset<kBitInByte> byte = 0;
    while(archive.tellg() < end_of_file) {
        uint16_t word_size = 0;
        uint8_t size_file_name = 0;
        uint32_t size_file = 0;

        std::string coded_word_size;
        while (length_of_string < LengthOfCodedWord(kMaxOfWordSize)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_word_size = string_from_file.substr(0, LengthOfCodedWord(kMaxOfWordSize));
        std::string uncoded_word_size = FileDecoding(coded_word_size);
        std::bitset<kMaxOfWordSize> word_size_in_bits = 0;
        for (char k = 0; k < kMaxOfWordSize; ++k) {
            if (uncoded_word_size[k] == '1') {
                word_size_in_bits |= (1 << (15 - k));
            }
        }
        word_size = word_size_in_bits.to_ulong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxOfWordSize));
        length_of_string -= LengthOfCodedWord(kMaxOfWordSize);

        std::string coded_size_file_name;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFileName)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kMaxSizeOfFileName;
        }
        coded_size_file_name = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFileName));
        std::string uncoded_size_file_name = ConversionStringToBytes(FileDecoding(coded_size_file_name));
        size_file_name = static_cast<uint8_t>(uncoded_size_file_name[0]);
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFileName));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFileName);

        std::string coded_file_name;
        while (length_of_string < LengthOfCodedWord(size_file_name * kBitInByte)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_file_name = string_from_file.substr(0, LengthOfCodedWord(size_file_name * kBitInByte));
        file_name = ConversionStringToBytes(FileDecoding(coded_file_name));
        string_from_file = string_from_file.substr(LengthOfCodedWord(size_file_name * kBitInByte));
        length_of_string -= LengthOfCodedWord(size_file_name * kBitInByte);

        std::cout << file_name << '\n';

        std::string coded_size_file;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFile)) {
            archive.read(&symbol, kSizeOfChar);
            byte = symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_size_file = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFile));
        std::string uncoded_size_file = FileDecoding(coded_size_file);
        std::bitset<kMaxSizeOfFile> size_file_in_bits;
        for (char k = 0; k < kMaxSizeOfFile; ++k) {
            if (uncoded_size_file[k] == '1') {
                size_file_in_bits |= (1 << (31 - k));
            }
        }
        size_file = size_file_in_bits.to_ullong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFile));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFile);

        int64_t length_of_coded_file = (size_file / word_size) * LengthOfCodedWord(kBitInByte * word_size) +
                                   LengthOfCodedWord((size_file % word_size) * kBitInByte);

        int64_t skip = ceil(static_cast<double> (length_of_coded_file - length_of_string) / 8);
        archive.seekg(skip, std::ios_base::cur);
        length_of_string = 0;
        string_from_file = "";
    }
    archive.close();
}

void Append(const std::string& archive_name, const std::string& path, uint16_t word_size, const std::string& enter_password) {
    std::fstream archive(archive_name  + ".haf", std::fstream::binary | std::fstream::in | std::fstream::out);
    if (!archive.is_open()) {
        std::cout << "archive doesn't exist";
        return;
    }
    char symbol;
    archive.read(&symbol, kSizeOfChar);
    int password_length = symbol + '0';
    std::string password;
    for (int i = 0; i < password_length; ++i) {
        archive.read(&symbol, kSizeOfChar);
        password += symbol;
    }

    if (enter_password != password) {
        std::cout << "wrong password or no password entered" << '\n';
        return;
    }

    std::string string_to_record;
    archive.seekg(0, std::ios::end);
    std::bitset<kMaxOfWordSize> word_size_in_bits = word_size;
    std::string uncoded_word_size = word_size_in_bits.to_string();
    std::string coded_word_size = FileCoding(uncoded_word_size);

    char byte = 0;
    uint32_t length_of_header;
    string_to_record += coded_word_size;

    std::string file_name = NameOfFile(path);
    uint32_t size_file = SizeOfFile(path);
    std::ifstream file(path, std::fstream::binary);
    if (!file.is_open()) {
        std::cout << "file \"" << file_name << "\" not found" << '\n';
        return;
    }

    uint8_t size_file_name = file_name.length();

    std::bitset<kMaxSizeOfFileName> size_file_name_in_bits = size_file_name;
    std::string uncoded_size_file_name = size_file_name_in_bits.to_string();
    std::string coded_size_file_name = FileCoding(uncoded_size_file_name);

    std::bitset<kMaxSizeOfFile> size_file_in_bits = size_file;
    std::string uncoded_size_file = size_file_in_bits.to_string();
    std::string coded_size_file = FileCoding(uncoded_size_file);

    std::string coded_file_name = FileCoding(ConversionStringToBits(file_name));

    length_of_header = coded_word_size.length() + coded_size_file.length() + coded_size_file_name.length() + coded_file_name.length();
    string_to_record += coded_size_file_name;
    string_to_record += coded_file_name;
    string_to_record += coded_size_file;


    for (int j = 0; j < length_of_header / kBitInByte; ++j) {
        std::string byte_in_string = string_to_record.substr(j * kBitInByte, kBitInByte);
        for (char k = 0; k < kBitInByte; ++k) {
            if (byte_in_string[k] == '1') {
                byte |= (1 << (7 - k));
            }
        }
        archive.write(&byte, kSizeOfChar);
        byte = 0;
    }
    string_to_record = string_to_record.substr(length_of_header - length_of_header % kBitInByte);

    std::string uncoded_word;
    while(file.read(&symbol, kSizeOfChar)) {
        uncoded_word += symbol;
        if (uncoded_word.length() == word_size) {
            string_to_record += FileCoding(ConversionStringToBits(uncoded_word));
            for (int j = 0; j < string_to_record.length() / kBitInByte; ++j) {
                std::string byte_in_string = string_to_record.substr(j * kBitInByte, kBitInByte);
                for (char k = 0; k < kBitInByte; ++k) {
                    if (byte_in_string[k] == '1') {
                        byte |= (1 << (7 - k));
                    }
                }
                archive.write(&byte, kSizeOfChar);
                byte = 0;
            }
            string_to_record = string_to_record.substr(string_to_record.length() - string_to_record.length() % kBitInByte);
            uncoded_word = "";
        }
    }
    if (uncoded_word.length() != 0) {
        string_to_record += FileCoding(ConversionStringToBits(uncoded_word));
        for (int j = 0; j < string_to_record.length() / kBitInByte; ++j) {
            std::string byte_in_string = string_to_record.substr(j * kBitInByte, kBitInByte);
            for (char k = 0; k < kBitInByte; ++k) {
                if (byte_in_string[k] == '1') {
                    byte |= (1 << (7 - k));
                }
            }
            archive.write(&byte, kSizeOfChar);
            byte = 0;
        }
        string_to_record = string_to_record.substr(string_to_record.length() - string_to_record.length() % kBitInByte);
    }
    for (int k = 0; k < string_to_record.length(); ++k) {
        if (string_to_record[k] == '1') {
            byte |= (1 << (7 - k));
        }
    }
    if (string_to_record.length() != 0)
        archive.write(&byte, kSizeOfChar);
    string_to_record = "";
    byte = 0;
    file.close();
    archive.close();
}

void Concatenate(const std::string& archive1_name, const std::string& archive2_name, const std::string& archive_name) {
    std::ofstream file(archive_name  + ".haf", std::ifstream::binary);
    std::ifstream archive1(archive1_name  + ".haf", std::ifstream::binary);
    std::ifstream archive2(archive2_name  + ".haf", std::ifstream::binary);
    if (!archive1.is_open() || !archive2.is_open()) {
        std::cout << "archive doesn't exist";
        return;
    }

    uint64_t end_of_file = SizeOfFile(archive1_name);
    while(archive1.tellg() < end_of_file) {
        char symbol;
        archive1.read(&symbol, kSizeOfChar);
        file.write(&symbol, kSizeOfChar);
    }

    end_of_file = SizeOfFile(archive2_name);
    while(archive2.tellg() < end_of_file) {
        char symbol;
        archive2.read(&symbol, kSizeOfChar);
        file.write(&symbol, kSizeOfChar);
    }

    file.close();
    archive1.close();
    archive2.close();
}

void Delete(const std::string& archive_name, const std::string& file_to_delete, const std::string& enter_password) {
    std::ifstream archive_for_reading(archive_name  + ".haf", std::ifstream::binary);
    if (!archive_for_reading.is_open()) {
        std::cout << "archive doesn't exist";
        return;
    }
    char symbol;
    archive_for_reading.read(&symbol, kSizeOfChar);
    int password_length = symbol + '0';
    std::string password;
    for (int i = 0; i < password_length; ++i) {
        archive_for_reading.read(&symbol, kSizeOfChar);
        password += symbol;
    }

    if (enter_password != password) {
        std::cout << "wrong password or no password entered" << '\n';
        return;
    }

    std::ofstream additional_file_for_writing(archive_name + "add.haf", std::ofstream::binary);
    std::string file_name;
    std::string string_from_file;
    int64_t length_of_string = 0;

    uint64_t end_of_file = SizeOfFile(archive_name  + ".haf");
    std::bitset<kBitInByte> byte = 0;
    while(archive_for_reading.tellg() < end_of_file) {
        uint16_t word_size = 0;
        uint8_t size_file_name = 0;
        uint64_t size_file = 0;
        std::string header;

        std::string coded_word_size;
        while (length_of_string < LengthOfCodedWord(kMaxOfWordSize)) {
            archive_for_reading.read(&symbol, kSizeOfChar);
            byte = symbol;
            header += symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_word_size = string_from_file.substr(0, LengthOfCodedWord(kMaxOfWordSize));
        std::string uncoded_word_size = FileDecoding(coded_word_size);
        std::bitset<kMaxOfWordSize> word_size_in_bits = 0;
        for (char k = 0; k < kMaxOfWordSize; ++k) {
            if (uncoded_word_size[k] == '1') {
                word_size_in_bits |= (1 << (15 - k));
            }
        }
        word_size = word_size_in_bits.to_ulong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxOfWordSize));
        length_of_string -= LengthOfCodedWord(kMaxOfWordSize);

        std::string coded_size_file_name;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFileName)) {
            archive_for_reading.read(&symbol, kSizeOfChar);
            byte = symbol;
            header += symbol;
            string_from_file += byte.to_string();
            length_of_string += kMaxSizeOfFileName;
        }
        coded_size_file_name = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFileName));
        std::string uncoded_size_file_name = ConversionStringToBytes(FileDecoding(coded_size_file_name));
        size_file_name = static_cast<uint8_t>(uncoded_size_file_name[0]);
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFileName));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFileName);

        std::string coded_file_name;
        while (length_of_string < LengthOfCodedWord(size_file_name * kBitInByte)) {
            archive_for_reading.read(&symbol, kSizeOfChar);
            byte = symbol;
            header += symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_file_name = string_from_file.substr(0, LengthOfCodedWord(size_file_name * kBitInByte));
        file_name = ConversionStringToBytes(FileDecoding(coded_file_name));
        string_from_file = string_from_file.substr(LengthOfCodedWord(size_file_name * kBitInByte));
        length_of_string -= LengthOfCodedWord(size_file_name * kBitInByte);

        std::string coded_size_file;
        while (length_of_string < LengthOfCodedWord(kMaxSizeOfFile)) {
            archive_for_reading.read(&symbol, kSizeOfChar);
            byte = symbol;
            header += symbol;
            string_from_file += byte.to_string();
            length_of_string += kBitInByte;
        }
        coded_size_file = string_from_file.substr(0, LengthOfCodedWord(kMaxSizeOfFile));
        std::string uncoded_size_file = FileDecoding(coded_size_file);
        std::bitset<kMaxSizeOfFile> size_file_in_bits;
        for (char k = 0; k < kMaxSizeOfFile; ++k) {
            if (uncoded_size_file[k] == '1') {
                size_file_in_bits |= (1 << (31 - k));
            }
        }
        size_file = size_file_in_bits.to_ullong();
        string_from_file = string_from_file.substr(LengthOfCodedWord(kMaxSizeOfFile));
        length_of_string -= LengthOfCodedWord(kMaxSizeOfFile);

        int64_t length_of_coded_file = (size_file / word_size) * LengthOfCodedWord(kBitInByte * word_size) +
                                   LengthOfCodedWord((size_file % word_size) * kBitInByte);

        int64_t skip = ceil(static_cast<double> (length_of_coded_file - length_of_string) / 8.0);

        if (file_name != file_to_delete) {
            for (int j = 0; j < header.length(); ++j) {
                additional_file_for_writing.write(&header[j], kSizeOfChar);
            }

            for (int64_t i = 0; i < skip; ++i) {
                archive_for_reading.read(&symbol, kSizeOfChar);
                additional_file_for_writing.write(&symbol, kSizeOfChar);
            }
        } else {
            archive_for_reading.seekg(skip, std::ios_base::cur);
        }
        length_of_string = 0;
        string_from_file = "";
        file_name = "";
    }
    archive_for_reading.close();
    std::ofstream archive_for_writing(archive_name  + ".haf", std::ofstream::binary);
    additional_file_for_writing.close();
    std::ifstream additional_file_for_reading(archive_name + "add.haf", std::ofstream::binary);
    end_of_file = SizeOfFile(archive_name + "add.haf");

    while(additional_file_for_reading.tellg() < end_of_file) {
        additional_file_for_reading.read(&symbol, kSizeOfChar);
        archive_for_writing.write(&symbol, kSizeOfChar);
    }
    additional_file_for_reading.close();
    std::remove((archive_name + "add.haf").c_str());
    archive_for_writing.close();
}
