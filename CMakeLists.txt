cmake_minimum_required(VERSION 3.14)
project(ModernCppErrorHandling)

# Require C++23 for std::expected
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure testing
enable_testing()

# Download and setup GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.14.0
)
FetchContent_MakeAvailable(googletest)

# Build tests executable
add_executable(pipeline_tests tests/pipeline_error_handling_test.cpp)
target_link_libraries(pipeline_tests PRIVATE gtest_main stdc++fs)  # Added stdc++fs
target_compile_features(pipeline_tests PRIVATE cxx_std_23)

# Add test target
add_test(NAME PipelineTests COMMAND pipeline_tests)