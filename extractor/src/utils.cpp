// utils.cpp
// String extraction logic

#include "utils.hpp"
#include <fstream>
#include <cctype>
#include <iostream>
#include <cmath>
#include <map>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

FileInfo extractFileInfo(const std::string& filepath) {
    std::filesystem::path path(filepath);
    FileInfo info;

    info.filename = path.filename().string();
    info.file_type = path.extension().string();
    info.file_size = std::filesystem::file_size(path);
    info.md5 = computeMD5(filepath);
    info.sha256 = computeSHA256(filepath);

    return info;
}

double calculateEntropy(const std::string& data) {
    std::map<char, int> freq;
    for (char c : data) freq[c]++;

    double entropy = 0.0;
    for (const auto& [c, count] : freq) {
        double p = static_cast<double>(count) / data.length();
        entropy -= p * std::log2(p);
    }
    return entropy;
}

void WriteToFile(std::ostream& outFile, const std::string& line) {
    outFile << line << "\n";
}

using json = nlohmann::json;

void writeJsonOutput(const std::string& filepath,
                     const FileInfo& fileInfo,
                     const std::vector<ImportFunction>& imports,
                     const std::vector<SectionInfo>& sections,
                     const std::vector<std::string>& strings)
{
    json j;
    j["file_info"] = {
        {"filename", fileInfo.filename},
        {"file_type", fileInfo.file_type},
        {"file_size", fileInfo.file_size},
        {"hashes", {
            {"md5", fileInfo.md5},
            {"sha256", fileInfo.sha256}
        }}
    };

    j["imports"] = json::array();
    for (const auto& imp : imports) {
        j["imports"].push_back({{"dll", imp.dll}, {"function", imp.function}});
    }

    j["sections"] = json::array();
    for (const auto& sec : sections) {
        j["sections"].push_back({
            {"name", sec.name.empty() ? "UNKNOWN" : sec.name},
            {"virtualSize", sec.virtualSize},
            {"rawSize", sec.rawSize}
        });
    }

    j["strings"] = strings;

    std::string jsonPath = filepath.substr(0, filepath.find_last_of('.')) + ".json";
    std::ofstream jf(jsonPath);
    jf << std::setw(4) << j;
    jf.close();
}

std::vector<std::string> filterHighEntropyStrings(const std::vector<std::string>& strings, double threshold) {
    std::vector<std::string> filtered;
    for (const auto& str : strings) {
        double entropy = calculateEntropy(str);
        if (entropy < threshold) {
            filtered.push_back(str);
        }
    }
    return filtered;
}

bool isPrintable(char c) {
    return std::isprint(static_cast<unsigned char>(c));
}

std::vector<std::string> extractAsciiStrings(const std::string& filepath, size_t minLength) {
    std::vector<std::string> strings;
    std::ifstream file(filepath, std::ios::binary);

    if (!file) return strings;

    std::string buffer;
    char ch;
    while (file.get(ch)) {
        if (isPrintable(ch)) {
            buffer += ch;
        } else {
            if (buffer.length() >= minLength) {
                strings.push_back(buffer);
            }
            buffer.clear();
        }
    }

    if (buffer.length() >= minLength) {
        strings.push_back(buffer);
    }

    return strings;
}
