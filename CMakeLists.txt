cmake_minimum_required(VERSION 3.10)
project(ticketing_system_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(complexsunnumber complexsunnumber.cpp)

# GoogleTest-based tests
include(GNUInstallDirs)

set(GTEST_VENDOR_DIR ${CMAKE_SOURCE_DIR}/third_party/googletest)

if(EXISTS ${GTEST_VENDOR_DIR})
	message(STATUS "Using vendored GoogleTest at ${GTEST_VENDOR_DIR}")
	add_subdirectory(${GTEST_VENDOR_DIR} EXCLUDE_FROM_ALL)
else()
	message(STATUS "Vendored GoogleTest not found; using FetchContent to download googletest")
	include(FetchContent)
	FetchContent_Declare(
		googletest
		URL https://github.com/google/googletest/archive/refs/tags/release-1.14.0.zip
	)
	FetchContent_MakeAvailable(googletest)
endif()

enable_testing()

add_executable(test_complex_gtest test_complex_gtest.cpp)
target_link_libraries(test_complex_gtest gtest_main)
add_test(NAME ComplexGTest COMMAND test_complex_gtest)

