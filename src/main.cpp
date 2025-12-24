#include <iostream>
#include <vector>

int main() {
    // A simple vector to prove C++17 is working
    std::vector<std::string> msg = {"Sentry-AI", "System", "Online"};

    std::cout << "---------------------------------" << std::endl;
    for (const auto& word : msg) {
        std::cout << word << " ";
    }
    std::cout << "\n---------------------------------" << std::endl;
    std::cout << "Build Configuration: SUCCESS" << std::endl;

    return 0;
}