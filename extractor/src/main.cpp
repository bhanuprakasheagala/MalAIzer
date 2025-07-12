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

    // Check if input file exists
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Error: File not found → " << filepath << "\n";
        return 1;
    }

    // Ensure outputs directory exists
    std::filesystem::create_directories("outputs");

    // Extract base name for output files
    std::filesystem::path sample_path(filepath);
    std::string base_name = sample_path.stem().string();
    std::string output_txt = "outputs/" + base_name + "_artifacts.txt";
    std::string output_json = "outputs/" + base_name + "_artifacts.json";

    // Open TXT output
    std::ofstream out(output_txt);
    if (!out) {
        std::cerr << "Failed to open output file: " << output_txt << "\n";
        return 1;
    }

    // ==== IMPORTS ====
    auto imports = extractImports(filepath);
    WriteToFile(out, "== IMPORTS ==");
    if (imports.empty()) {
        WriteToFile(out, "[No imports found]");
    } else {
        for (const auto& imp : imports) {
            WriteToFile(out, imp.dll + " : " + imp.function);
        }
    }

    // ==== SECTIONS ====
    auto sections = extractSections(filepath);
    WriteToFile(out, "\n== SECTIONS ==");
    if (sections.empty()) {
        WriteToFile(out, "[No sections found]");
    } else {
        for (const auto& sec : sections) {
            std::string secName = sec.name.empty() ? "[Unnamed]" : sec.name;
            WriteToFile(out, secName + " | VSize: " +
                std::to_string(sec.virtualSize) + " | RawSize: " +
                std::to_string(sec.rawSize));
        }
    }

    // ==== STRINGS ====
    WriteToFile(out, "\n== STRINGS ==");
    auto rawStrings = extractAsciiStrings(filepath, 4);
    auto filteredStrings = filterHighEntropyStrings(rawStrings, 4.5);
    if (filteredStrings.empty()) {
        WriteToFile(out, "[No printable strings or all filtered]");
    } else {
        for (const auto& str : filteredStrings) {
            WriteToFile(out, str);
        }
    }

    out.close();

    // ==== JSON OUTPUT ====
    writeJsonOutput(output_json, imports, sections, filteredStrings);
    std::cout << "Artifacts extracted to: " << output_txt << " and " << output_json << "\n";

    return 0;
}