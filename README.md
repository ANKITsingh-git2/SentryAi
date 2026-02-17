# SentryAI

SentryAI is a smart log analysis tool that uses the Groq API (Llama 3) to automatically detect errors in your log files and suggest fixes.

## Features
- **Smart Detection**: Finds "ERROR" patterns (customizable).
- **Context Awareness**: Captures lines before the error to give the AI context.
- **Parallel Processing**: Analyzes multiple errors simultaneously using C++ `std::async`.
- **Configurable**: Choose your model, search pattern, and context size.

## Prerequisites
- **Groq API Key**: You need a `GROQ_API_KEY` environment variable.
- **Docker** (Optional, for containerized usage).
- **CMake & GCC** (For building from source).

## Usage (CLI)

1. **Build**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

2. **Run**:
   ```bash
   export GROQ_API_KEY="your_key_here"
   ./sentry-ai -f /path/to/server.log
   ```

3. **Options**:
   - `-f, --file`: Path to the log file (Required).
   - `-p, --pattern`: Regex or string to search for (Default: "ERROR").
   - `-m, --model`: Groq model ID (Default: "llama-3.1-8b-instant").
   - `-c, --context`: Number of lines of context to include (Default: 5).

   **Example**:
   ```bash
   ./sentry-ai -f app.log -p "CRITICAL" -m "llama3-70b-8192" -c 10
   ```

## Usage (Docker)

1. **Build the Image**:
   ```bash
   docker build -t sentry-ai .
   ```

2. **Run the Container**:
   ```bash
   docker run -e GROQ_API_KEY=$GROQ_API_KEY -v $(pwd)/test.log:/app/test.log sentry-ai -f test.log
   ```

## License
MIT
