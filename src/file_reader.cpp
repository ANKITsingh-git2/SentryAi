#include "../include/file_reader.h"
#include <iostream>
#include <fstream>
#include <deque> //  for the sliding window

std::vector<LogEntry> process_log_file(const std::string& filepath) {
    std::vector<LogEntry> found_errors;
    std::ifstream file(filepath);
    
    // The Sliding Window Buffer (holds last 5 lines)
    std::deque<std::string> context_buffer;
    const int CONTEXT_SIZE = 5;

    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open file: " << filepath << std::endl;
        return found_errors;
    }

    std::string line;
    int line_count = 0;

    while (std::getline(file, line)) {
        line_count++;

        // 1. Check for "ERROR" keyword
        if (line.find("ERROR") != std::string::npos) {
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
        if (context_buffer.size() > CONTEXT_SIZE) {
            context_buffer.pop_front(); // Remove the oldest line
        }
    }

    file.close();
    return found_errors;
}