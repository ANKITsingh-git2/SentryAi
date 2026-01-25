#include <iostream>
#include <cstdlib> // For std::getenv
#include "../include/CLI11.hpp" 
#include "../include/file_reader.h"
#include "../include/json_helper.h"
#include "../include/http_client.h"

int main(int argc, char** argv) {
    // 1. Load API Key securely
    const char* env_api_key = std::getenv("GROQ_API_KEY");
    if (!env_api_key) {
        std::cerr << "[CRITICAL] GROQ_API_KEY not found in environment variables." << std::endl;
        std::cerr << "Run: export GROQ_API_KEY='your_key_here'" << std::endl;
        return 1;
    }
    std::string api_key = env_api_key;

    // 2. CLI Setup
    CLI::App app{"Sentry-AI"};
    std::string filename = "default.log";
    app.add_option("-f,--file", filename, "Path to log file")->required();
    CLI11_PARSE(app, argc, argv);

    // 3. Process Logs
    std::cout << "Scanning logs..." << std::endl;
    std::vector<LogEntry> errors = process_log_file(filename);

    if (errors.empty()) {
        std::cout << "No errors found." << std::endl;
        return 0;
    }

    // 4. AI Analysis (Analyzing the first error found)
    std::cout << "Analyzing Critical Error with Llama 3..." << std::endl;
    
    std::string payload = create_groq_payload(errors[0]);
    std::string ai_response = send_groq_request(payload, api_key);

    // 5. Output
    std::cout << "\n---------------- AI ANALYSIS ----------------" << std::endl;
    std::cout << ai_response << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    return 0;
}