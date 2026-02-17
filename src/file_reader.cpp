#include "../include/file_reader.h"
#include <deque> //  for the sliding window
#include <fstream>
#include <iostream>

std::vector<LogEntry> process_log_file(const std::string &filepath,
                                       const std::string &search_pattern,
                                       int context_size) {
  std::vector<LogEntry> found_errors;
  std::ifstream file(filepath);

  // The Sliding Window Buffer
  std::deque<std::string> context_buffer;

  if (!file.is_open()) {
    std::cerr << "[ERROR] Could not open file: " << filepath << std::endl;
    return found_errors;
  }

  std::string line;
  int line_count = 0;

  while (std::getline(file, line)) {
    line_count++;

    // 1. Check for the Search Pattern
    if (line.find(search_pattern) != std::string::npos) {
      // Snapshot the current state!
      LogEntry entry;
      entry.line_number = line_count;
      entry.message = line;

      // Copy the deque into our vector
      entry.context.assign(context_buffer.begin(), context_buffer.end());

      found_errors.push_back(entry);
    }

    // 2. Maintain the Sliding Window
    context_buffer.push_back(line);
    if (context_buffer.size() > context_size) {
      context_buffer.pop_front(); // Remove the oldest line
    }
  }

  file.close();
  return found_errors;
}