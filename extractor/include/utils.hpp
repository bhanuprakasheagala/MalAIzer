// utils.hpp
// Utility functions for string extraction and formatting

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include "pe_parser.hpp"
#include "hash_utils.hpp"

bool isPrintable(char c);
std::vector<std::string> extractAsciiStrings(const std::string& filepath, size_t minLength = 4);

// New utility additions
struct FileInfo {
    std::string filename;
    std::string file_type;
    size_t file_size;
    std::string md5;
    std::string sha256;
};

// New functions
FileInfo extractFileInfo(const std::string& filepath);

double calculateEntropy(const std::string& data);
std::vector<std::string> filterHighEntropyStrings(const std::vector<std::string>& strings, double threshold = 4.5);
void WriteToFile(std::ostream& outFile, const std::string& line);
void writeJsonOutput(const std::string& filepath,
                     const FileInfo& fileInfo,
                     const std::vector<ImportFunction>& imports,
                     const std::vector<SectionInfo>& sections,
                     const std::vector<std::string>& strings);

#endif
