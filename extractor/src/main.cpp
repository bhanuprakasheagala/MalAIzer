// main.cpp
// Entry point: takes a PE file path, extracts data, and outputs artifacts

#include "pe_parser.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./malalyzer <path_to_pe_file>\n";
        return 1;
    }

    std::string filepath = argv[1];
    std::ofstream output("outputs/artifacts.txt");

    output << "== IMPORTS ==\n";
    for (const auto& imp : extractImports(filepath)) {
        output << imp.dll << " : " << imp.function << "\n";
    }

    output << "\n== SECTIONS ==\n";
    for (const auto& sec : extractSections(filepath)) {
        output << sec.name << " | VSize: " << sec.virtualSize
               << " | RawSize: " << sec.rawSize << "\n";
    }

    output << "\n== STRINGS ==\n";
    for (const auto& str : extractAsciiStrings(filepath)) {
        output << str << "\n";
    }

    output.close();
    std::cout << "Artifacts saved to outputs/artifacts.txt\n";
    return 0;
}
