#include "HammingCode.h"
#include <iostream>
#include <vector>
#include <cstring>

void SetPassword(const std::string& archive_name, const std::string& password_to_set, const std::string& enter_password);

void ExtractFiles(const std::string& archive_name,  std::vector<std::string> files, const std::string& enter_password);

void CreateArchive(const std::string& file_name, std::vector<std::string> files, uint16_t word_size, const std::string& password);

void List(const std::string& archive_name, const std::string& enter_password);

void Append(const std::string& archive_name, const std::string& file_name, uint16_t word_size, const std::string& enter_password);

void Concatenate(const std::string& archive1_name, const std::string& archive2_name, const std::string& archive_name);

void Delete(const std::string& archive_name, const std::string& file_to_delete, const std::string& enter_password);