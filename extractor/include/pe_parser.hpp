// pe_parser.hpp
// This file is part of MalAIzer, a tool for analyzing and extracting information from PE files.

#ifndef PE_PARSER_HPP
#define PE_PARSER_HPP

#include <string>
#include <vector>

// Structure to store API import info
struct ImportFunction {
    std::string dll;
    std::string function;
};

// Structure to store section info
struct SectionInfo {
    std::string name;
    uint32_t virtualSize;
    uint32_t rawSize;
};

// Core parsing functions
std::vector<ImportFunction> extractImports(const std::string& filepath);
std::vector<SectionInfo> extractSections(const std::string& filepath);
std::vector<std::string> extractStrings(const std::string& filepath);

#endif