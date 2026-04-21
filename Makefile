CXX ?= g++
CXXFLAGS ?= -g -std=c++17 -Iinclude

SOURCES = complexsunnumber.cpp
TARGET = complexsunnumber
TEST_SRC = test_complex.cpp
TEST_TARGET = test_complex

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES)	
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)


test: build_test
	./test_complex_gtest

.PHONY: build_test
build_test:
	@if command -v cmake >/dev/null 2>&1; then \
		mkdir -p build && cd build && cmake .. && cmake --build . --target test_complex_gtest; \
	else \
		echo "Attempting to vendor GoogleTest and retrying..."; \
		./scripts/vendor_gtest.sh || { echo "Vendoring failed"; exit 1; }; \
		mkdir -p build && cd build && cmake .. && cmake --build . --target test_complex_gtest; \
	fi

vendor-gtest:
	@./scripts/vendor_gtest.sh release-1.14.0

$(TEST_TARGET): $(TEST_SRC)
	# Try to build GoogleTest-based test using CMake (will FetchContent googletest).
	# If cmake is not available or the CMake build fails, fall back to a simple assert-based test build.
	@if command -v cmake >/dev/null 2>&1; then \
		mkdir -p build && cd build && cmake .. && cmake --build . --target test_complex_gtest && cp test_complex_gtest ..; \
		if [ $$? -ne 0 ]; then \
			echo "CMake build failed, falling back to assert-based test."; \
			$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_TARGET); \
		fi; \
	else \
		echo "cmake not found, building fallback custom test runner."; \
		$(CXX) $(CXXFLAGS) test_complex_custom.cpp -o $(TEST_TARGET); \
	fi

clean:
	rm -f $(TARGET) test_complex_gtest test_complex
