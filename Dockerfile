FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    curl \
    wget \
    unzip \
    python3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Copy project files
COPY . /workspace

# Build and run tests
RUN mkdir -p build && cd build && cmake .. && cmake --build . --target test_complex_gtest

CMD ["/bin/bash"]
