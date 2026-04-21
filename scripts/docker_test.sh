#!/usr/bin/env bash
# Build and run the dockerized test image
set -euo pipefail
IMAGE_NAME="ticketing-system-test"

docker build -t ${IMAGE_NAME} .

echo "Running tests inside container..."
docker run --rm ${IMAGE_NAME} /bin/bash -lc "cd build && ./test_complex_gtest"

echo "Docker tests finished."