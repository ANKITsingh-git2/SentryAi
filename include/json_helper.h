#pragma once
#include "json.hpp"
#include "file_reader.h"
#include <string>

// to amke typing easier
using json = nlohmann::json;

// convert a log entry into a groq-ready json str
std::string create_groq_payload(const LogEntry& log) {
    // 1. Construct the prompt content
    std::string content = "Analyze this error log and provide a fix:\n\nContext:\n";
    for (const auto& line : log.context) {
        content += line + "\n";
    }
    content += "Error Line: " + log.message;

    // 2. Build the JSON object structure
    // Notice how similar this looks to Python dictionaries!
    json payload = {
        {"model", "llama3-8b-8192"},
        {"messages", {
            {
                {"role", "user"},
                {"content", content}
            }
        }}
    };

    // 3. Dump to string (serialization)
    return payload.dump(); 
}

