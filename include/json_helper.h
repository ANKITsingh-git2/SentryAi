#pragma once
#include "file_reader.h"
#include "json.hpp"
#include <string>

// to amke typing easier
using json = nlohmann::json;

// convert a log entry into a groq-ready json str
std::string
create_groq_payload(const LogEntry &log,
                    const std::string &model = "llama-3.1-8b-instant") {
  // 1. Construct the prompt content
  std::string content =
      "Analyze this error log and provide a fix:\n\nContext:\n";
  for (const auto &line : log.context) {
    content += line + "\n";
  }
  content += "Error Line: " + log.message;

  // 2. Build the JSON object structure
  // Notice how similar this looks to Python dictionaries!
  json payload = {{"model", model},
                  {"messages", {{{"role", "user"}, {"content", content}}}}};

  // 3. Dump to string (serialization)
  return payload.dump();
}

std::string parse_groq_response(const std::string &raw_json) {
  try {
    // 1. Parse the string into a JSON object
    auto json_data = json::parse(raw_json);

    // 2. Navigate the path: choices -> [0] -> message -> content
    // This matches the structure you saw in your terminal output!
    if (json_data.contains("choices") && !json_data["choices"].empty()) {
      return json_data["choices"][0]["message"]["content"];
    } else if (json_data.contains("error")) {
      return "API Error: " + json_data["error"]["message"].get<std::string>();
    }
    return "Error: Unexpected JSON format.";
  } catch (const std::exception &e) {
    return "JSON Parsing Error: " + std::string(e.what());
  }
}
