cmake_minimum_required(VERSION 3.10)
project(malalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Include paths ===
include_directories(
    ${CMAKE_SOURCE_DIR}/../pe-parse/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/../json/include
)

# === Add executable ===
add_executable(malalyzer
    src/main.cpp
    src/pe_parser.cpp
    src/utils.cpp
    src/hash_utils.cpp
)

# === Link PE-parse ===
find_library(PE_PARSE_LIB pe-parse
    PATHS ${CMAKE_SOURCE_DIR}/../pe-parse/build/pe-parser-library
    NO_DEFAULT_PATH
)
target_link_libraries(malalyzer ${PE_PARSE_LIB})

# === Optional: Link pthread for entropy thread safety (if needed) ===
find_package(Threads REQUIRED)
target_link_libraries(malalyzer Threads::Threads)


# === Compile options ===
add_compile_options(-Wall -Wextra -Wno-deprecated-declarations)