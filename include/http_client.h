#pragma once
#include <string>

// Sends a JSON string to the specific URL using the API Key
// Returns the server's response (string)
std::string send_groq_request(const std::string& json_payload, const std::string& api_key);