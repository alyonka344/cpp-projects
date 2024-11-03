#pragma once

#include <fstream>
#include <iostream>

void ReadUpToNullCharacter(std::fstream& file, std::string& variable);

void ReadingToSize(std::fstream& file, std::string& variable, uint32_t size);

uint64_t ReadingANumber(std::fstream& file, uint32_t size);
