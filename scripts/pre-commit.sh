#!/usr/bin/env bash
# Pre-commit script: run tests before allowing commit
set -e
echo "Running pre-commit tests..."
if command -v cmake >/dev/null 2>&1; then
  mkdir -p build
  cd build
  cmake ..
  cmake --build . --target test_complex_gtest
  ./test_complex_gtest
else
  echo "cmake not found — please install CMake to enable pre-commit tests (or run tests manually)."
  exit 1
fi

echo "Pre-commit tests passed."
