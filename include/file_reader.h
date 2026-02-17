#pragma once
#include <string>
#include <vector>

// A struct to hold a single "Incident"
struct LogEntry {
  int line_number;
  std::string message;
  std::vector<std::string> context; // The lines leading up to the error
};

//  return a vector of LogEntry
std::vector<LogEntry>
process_log_file(const std::string &filepath,
                 const std::string &search_pattern = "ERROR",
                 int context_size = 5);