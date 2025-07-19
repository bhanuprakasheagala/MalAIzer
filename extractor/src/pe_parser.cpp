// pe_parser.cpp
// PE parsing functions using pe-parse

#include "pe_parser.hpp"
#include <pe-parse/parse.h>
#include <iostream>

using namespace peparse;

std::vector<ImportFunction> extractImports(const std::string& filepath) {
    std::vector<ImportFunction> imports;
    parsed_pe* pe = ParsePEFromFile(filepath.c_str());
    if (!pe) return imports;

    IterImpVAString(pe, [](void* payload, const VA&, const std::string& dll, const std::string& func) -> int{
       auto* imports = static_cast<std::vector<ImportFunction>*>(payload);
            imports->push_back({ dll, func });
            return 1; // continue iteration
        },
        &imports
    );

    DestructParsedPE(pe);
    return imports;
}

std::vector<SectionInfo> extractSections(const std::string& filepath) {
    std::vector<SectionInfo> sections;
    parsed_pe* pe = ParsePEFromFile(filepath.c_str());
    if (!pe) return sections;

    IterSec(pe, [](void* payload, const VA&, const std::string& name, const image_section_header& s, const bounded_buffer*) -> int {
        auto* sections = static_cast<std::vector<SectionInfo>*>(payload);
        SectionInfo si;
        si.name = name;
        si.virtualSize = s.Misc.VirtualSize;
        si.rawSize = s.SizeOfRawData;
        sections->push_back(si);
        return 0; // continue iteration
    }, &sections);

    DestructParsedPE(pe);
    return sections;
}
