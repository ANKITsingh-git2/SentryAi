#include<iostream>
#include<string>
#include "../include/CLI11.hpp"
#include "../include/file_reader.h"

int main(int argc, char** argv){
    CLI::App app{"Sentry-AI: High performance log analyzer"};
    std::string filename = "default.log";
    app.add_option("-f,--file",filename,"path to log file")->required();
    CLI11_PARSE(app, argc, argv);

    std::cout << "scanning" << filename << "..." << std::endl;

    // get structured errors
    std::vector<LogEntry> errors = process_log_file(filename);

    std::cout << "Found " << errors.size() << " critical events.\n" << std::endl;

    // Iterate and Print
    for (const auto& error : errors) {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "[CRITICAL] Line " << error.line_number << std::endl;
        
        std::cout << "Context:" << std::endl;
        for (const auto& ctx_line : error.context) {
            std::cout << "   | " << ctx_line << std::endl;
        }
        
        std::cout << ">> " << error.message << std::endl; // The Error itself
    }

    return 0;
}



