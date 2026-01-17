#include <iostream>
#include "../include/CLI11.hpp" 
#include "../include/file_reader.h"
#include "../include/json_helper.h"
#include "../include/http_client.h" 

int main(int argc, char** argv) {
    CLI::App app{"Sentry-AI"};
    std::string filename = "default.log";
    app.add_option("-f,--file", filename, "Path to log file");
    CLI11_PARSE(app, argc, argv);

    std::cout << "Checking Network Connectivity..." << std::endl;
    
    if (check_internet_connection()) {
        std::cout << "[SUCCESS] Connected to the Internet." << std::endl;
    } else {
        std::cout << "[ERROR] No Internet Connection." << std::endl;
        return 1;
    }

    return 0;
}