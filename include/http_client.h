#pragma once
#include <string>

// Sends a JSON string to the specific URL using the API Key
// Sends the JSON payload to Groq API using libcurl
std::string send_groq_request(const std::string &json_payload,
                              const std::string &api_key,
                              const std::string &model);