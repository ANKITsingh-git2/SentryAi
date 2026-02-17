# Stage 1: Build
FROM gcc:latest AS builder

# Install CMake
RUN apt-get update && apt-get install -y cmake

WORKDIR /app

# Copy source
COPY . .

# Build
RUN mkdir build && cd build && cmake .. && make

# Stage 2: Runtime
FROM debian:bookworm-slim

# Install runtime dependencies (libcurl)
RUN apt-get update && apt-get install -y libcurl4 ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy binary from builder
COPY --from=builder /app/build/sentry-ai .

# Entrypoint
ENTRYPOINT ["./sentry-ai"]
