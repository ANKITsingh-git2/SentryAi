#include <iostream>
#include <string>
#include "../include/CLI11.hpp" 
#include "../include/file_reader.h"
#include "../include/json_helper.h" 

int main(int argc, char** argv) {
    CLI::App app{"Sentry-AI: High Performance Log Analyzer"};
    std::string filename = "default.log";
    app.add_option("-f,--file", filename, "Path to log file")->required();
    CLI11_PARSE(app, argc, argv);

    std::vector<LogEntry> errors = process_log_file(filename);

    if (errors.empty()) {
        std::cout << "No errors found." << std::endl;
        return 0;
    }

    // TEST: Take the first error found and convert it to JSON
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Testing JSON Conversion for Groq API:" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    
    std::string payload = create_groq_payload(errors[0]);
    
    std::cout << payload << std::endl;

    return 0;
}