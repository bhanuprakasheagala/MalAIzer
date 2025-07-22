#include "hash_utils.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

// --- Minimal MD5 implementation ---
#include "md5.hpp"   
#include "sha256.hpp" 

std::vector<unsigned char> readFileBytes(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

std::string computeMD5(const std::string& filepath) {
    auto data = readFileBytes(filepath);
    return MD5::hash(data);
}

std::string computeSHA256(const std::string& filepath) {
    auto data = readFileBytes(filepath);
    return SHA256::hash(data);
}
