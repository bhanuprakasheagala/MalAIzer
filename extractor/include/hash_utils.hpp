#pragma once
#include <string>

// Returns lowercase hexadecimal string
std::string computeMD5(const std::string& filepath);
std::string computeSHA256(const std::string& filepath);