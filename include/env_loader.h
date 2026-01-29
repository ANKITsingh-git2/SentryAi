#ifndef ENV_LOADER_H
#define ENV_LOADER_H

#include <string>

/**
 * @brief Loads environment variables from a .env file into the system
 * environment.
 *
 * @param filepath Path to the .env file (default: ".env")
 */
void load_env_file(const std::string &filepath = ".env");

#endif // ENV_LOADER_H
