#include <iostream>
#include <string>
#include "../include/CLI11.hpp" // parse cmd line arguments

int main(int argc, char** argv) {
    // 1. Create the App instance
    CLI::App app{"Sentry-AI: High Performance Log Analyzer"};

    // 2. Define variables to hold user input
    std::string filename = "default.log"; // Default value
    std::string level = "ERROR";

    // 3. Setup the flags
    // "filename" will store the value passed after -f or --file
    app.add_option("-f,--file", filename, "Path to the log file to analyze")->required();
    
    // "level" is optional (default is ERROR)
    app.add_option("-l,--level", level, "Filter level (INFO, WARN, ERROR)");

    // 4. Parse the arguments
    CLI11_PARSE(app, argc, argv);

    // 5. Prove it works
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "[Target] File : " << filename << std::endl;
    std::cout << "[Filter] Level: " << level << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    // Simulate "Systems Engineering" check
    std::cout << "Initializing Engine..." << std::endl;

    return 0;
}