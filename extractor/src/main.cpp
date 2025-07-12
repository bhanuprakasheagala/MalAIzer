// main.cpp
// Entry point: takes a PE file path, extracts data, and outputs artifacts

#include "pe_parser.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./malalyzer <path_to_pe_file>\n";
        return 1;
    }

    std::string filepath = argv[1];

    // Ensure outputs directory exists
    std::filesystem::create_directories("outputs");

    // Get base filename (without extension) for output file
    std::filesystem::path sample_path(filepath);
    std::string base_name = sample_path.stem().string();
    std::string output_file = "outputs/" + base_name + "_artifacts.txt";

    std::ofstream output(output_file);
    if (!output) {
        std::cerr << "Failed to open output file: " << output_file << "\n";
        return 1;
    }

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
    std::cout << "Artifacts saved to " << output_file << "\n";
}