#pragma once
#include <iostream>
#include <filesystem>
#include <ostream>
#include <fstream>
#include <vector>
#include <cxxopts.hpp>
#include <iterator>

#ifdef _WIN32
#include <io.h>    // For _isatty() and _fileno() on Windows
#include <fcntl.h> // For _O_BINARY
#else
#include <unistd.h> // For isatty() and fileno() on Unix
#endif

constexpr size_t COMPRESSION_QUALITY_DEFLATE = 8;
constexpr size_t MAX_DECOMPRESSION_SIZE = 1024*1024*1024;

#ifdef SINFL_IMPLEMENTATION
constexpr const char* TOOL_NAME = "smallinflate";
#else
constexpr const char* TOOL_NAME = "smalldeflate";
#endif

#ifdef SINFL_IMPLEMENTATION
std::vector<char> DecompressData(const std::vector<char>& compData);
#else
std::vector<char> CompressData(const std::vector<char>& data);
#endif

int CompressOrDecompress(int argc, char** argv)
{
    namespace fs = std::filesystem;
    
    std::vector<char> buffer;

#ifdef _WIN32
    bool isTerminal = _isatty(_fileno(stdin));
    // Set stdin to binary mode to handle any input properly
    _setmode(_fileno(stdin), _O_BINARY);
#else
    bool isTerminal = isatty(fileno(stdin));
#endif

    if (!isTerminal) {
        buffer.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
    }
    
    fs::path outputFile {};
    
    if (buffer.empty())
    {
        cxxopts::Options options(TOOL_NAME, "Compression or decompression for files");

        options.add_options() //
            ("i,input", "The file to compress", cxxopts::value<fs::path>())
            ("o,output", "The output file", cxxopts::value<fs::path>())
            ("f,force", "If input and output are the same, write anyways", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage");

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << '\n';
            return EXIT_SUCCESS;
        }

        fs::path inputFile {};
        bool forced {};

        try {
            inputFile = result["input"].as<fs::path>().lexically_normal();
            outputFile = result["output"].as<fs::path>().lexically_normal();
            forced = result["force"].as<bool>();
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << '\n' << options.help() << '\n';
            return EXIT_FAILURE;
        }

        if (inputFile == outputFile && !forced) {
            std::cerr << "Output file is the same as the input file! Re-run with --force if this is what you intended.\n";
            return EXIT_FAILURE;
        }

        try {
            std::ifstream content(inputFile.string(), std::ios::binary);
            buffer.reserve(std::filesystem::file_size(inputFile));
            buffer.assign((std::istreambuf_iterator<char>(content)),
                          std::istreambuf_iterator<char>());
        } catch (const std::exception& ex) {
            std::cerr << "Error reading file: " << inputFile.string() << "\n-> " << ex.what() << '\n';
            return EXIT_FAILURE;
        }
    }

#ifdef SINFL_IMPLEMENTATION
    const std::vector<char> data = DecompressData(buffer);
#else
    const std::vector<char> data = CompressData(buffer);
#endif

    if (outputFile.empty()) {
        std::copy(data.begin(), data.end(), std::ostream_iterator<char>(std::cout));
    } else {
        auto out = std::ofstream(outputFile.string(), std::ios::binary);
        std::copy(data.begin(), data.end(), std::ostream_iterator<char>(out));
    }
    
    return EXIT_SUCCESS;
}
