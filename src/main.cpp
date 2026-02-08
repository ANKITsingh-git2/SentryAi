#include <iostream>
#include <cstdlib>
#include <vector>
#include <future> // <--- NEW: For Async tasks
#include "../include/CLI11.hpp" 
#include "../include/file_reader.h"
#include "../include/json_helper.h"
#include "../include/http_client.h"

int main(int argc, char** argv) {
    // 1. Load Key
    const char* env_api_key = std::getenv("GROQ_API_KEY");
    if (!env_api_key) {
        std::cerr << "[CRITICAL] GROQ_API_KEY not found." << std::endl;
        return 1;
    }
    std::string api_key = env_api_key;

    // 2. CLI
    CLI::App app{"Sentry-AI"};
    std::string filename = "default.log";
    app.add_option("-f,--file", filename, "Path to log file")->required();
    CLI11_PARSE(app, argc, argv);

    // 3. Scan File
    std::cout << "Scanning " << filename << "..." << std::endl;
    std::vector<LogEntry> errors = process_log_file(filename);

    if (errors.empty()) {
        std::cout << "No errors found." << std::endl;
        return 0;
    }

    std::cout << "Found " << errors.size() << " errors. Analyzing in parallel..." << std::endl;

    // 4. PARALLEL EXECUTION
    // We create a list of "Futures". Each future represents a background task.
    std::vector<std::future<std::string>> futures;

    for (const auto& error : errors) {
        // Prepare the payload locally
        std::string payload = create_groq_payload(error);

        // std::async launches the lambda function in a new thread
        futures.push_back(std::async(std::launch::async, [payload, api_key]() {
            // This happens in the background!
            std::string raw = send_groq_request(payload, api_key);
            return parse_groq_response(raw);
        }));
    }

    // 5. Collect Results
    // The main thread waits here until specific tasks finish
    for (size_t i = 0; i < futures.size(); ++i) {
        std::cout << "\nWaiting for Error #" << (i + 1) << "..." << std::endl;
        
        // .get() blocks until THIS specific thread is done
        std::string analysis = futures[i].get(); 

        std::cout << "================ ERROR " << (i + 1) << " REPORT ================" << std::endl;
        std::cout << analysis << std::endl;
    }

    return 0;
}