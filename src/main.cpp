#include "../include/CLI11.hpp"
#include "../include/file_reader.h"
#include "../include/http_client.h"
#include "../include/json_helper.h"
#include <cstdlib>
#include <future> 
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  // 1. Load Key
  const char *env_api_key = std::getenv("GROQ_API_KEY");
  if (!env_api_key) {
    std::cerr << "[CRITICAL] GROQ_API_KEY not found." << std::endl;
    return 1;
  }
  std::string api_key = env_api_key;

  // 2. CLI
  CLI::App app{"Sentry-AI"};
  std::string filename = "default.log";
  std::string pattern = "ERROR";
  std::string model = "llama-3.1-8b-instant";
  int context = 5;

  app.add_option("-f,--file", filename, "Path to log file")->required();
  app.add_option("-p,--pattern", pattern,
                 "Regex/String to search for (default: ERROR)");
  app.add_option("-m,--model", model,
                 "Groq model to use (default: llama-3.1-8b-instant)");
  app.add_option("-c,--context", context, "Lines of context (default: 5)");

  CLI11_PARSE(app, argc, argv);

  // 3. Scan File
  std::cout << "Scanning " << filename << "..." << std::endl;
  std::cout << "Pattern: " << pattern << " | Context: " << context
            << " | Model: " << model << std::endl;
  std::vector<LogEntry> errors = process_log_file(filename, pattern, context);

  if (errors.empty()) {
    std::cout << "No errors found." << std::endl;
    return 0;
  }

  std::cout << "Found " << errors.size() << " errors. Analyzing in parallel..."
            << std::endl;

  // 4. PARALLEL EXECUTION
  // We create a list of "Futures". Each future represents a background task.
  std::vector<std::future<std::string>> futures;

  for (const auto &error : errors) {
    // Prepare the payload locally
    std::string payload = create_groq_payload(error, model);

    // std::async launches the lambda function in a new thread
    futures.push_back(
        std::async(std::launch::async, [payload, api_key, model]() {
          // This happens in the background!
          std::string raw = send_groq_request(payload, api_key, model);
          return parse_groq_response(raw);
        }));
  }

  // 5. Collect Results
  // The main thread waits here until specific tasks finish
  for (size_t i = 0; i < futures.size(); ++i) {
    std::cout << "\nWaiting for Error #" << (i + 1) << "..." << std::endl;

    // .get() blocks until THIS specific thread is done
    std::string analysis = futures[i].get();

    std::cout << "================ ERROR " << (i + 1)
              << " REPORT ================" << std::endl;
    std::cout << analysis << std::endl;
  }

  return 0;
}