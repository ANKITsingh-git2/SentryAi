#include "../include/env_loader.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

// Helper to trim whitespace
static std::string trim(const std::string &str) {
  size_t first = str.find_first_not_of(" \t\r\n");
  if (std::string::npos == first) {
    return str;
  }
  size_t last = str.find_last_not_of(" \t\r\n");
  return str.substr(first, (last - first + 1));
}

void load_env_file(const std::string &filepath) {
  std::string actual_path = filepath;
  std::ifstream file(actual_path);

  // If not found in current directory and we are looking for default .env, try
  // parent directory
  if (!file.is_open() && filepath == ".env") {
    actual_path = "../.env";
    file.open(actual_path);
  }

  if (!file.is_open()) {
    // Still not found
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::string trimmed_line = trim(line);
    // Ignore empty lines and comments
    if (trimmed_line.empty() || trimmed_line[0] == '#') {
      continue;
    }

    size_t delimiter_pos = trimmed_line.find('=');
    if (delimiter_pos != std::string::npos) {
      std::string key = trim(trimmed_line.substr(0, delimiter_pos));
      std::string value = trim(trimmed_line.substr(delimiter_pos + 1));

      // Remove quotes if present
      if (value.size() >= 2 &&
          ((value.front() == '"' && value.back() == '"') ||
           (value.front() == '\'' && value.back() == '\''))) {
        value = value.substr(1, value.size() - 2);
      }

      // Only set if not already set (allow system env to override)
      if (std::getenv(key.c_str()) == nullptr) {
        setenv(key.c_str(), value.c_str(), 1);
      }
    }
  }
  file.close();
}
