# ModernCppErrorHandling/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(ModernCppErrorHandling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Fetch Catch2 v3 (header-only) ───────────────────────────────────
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
  GIT_TAG         v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# ── Pipeline library (implementation you copied from the assignment) ─
add_library(pipeline STATIC
  src/pipeline.cpp
)
target_include_directories(pipeline PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ── Unit tests ─────────────────────────────────────────────────────
add_executable(pipeline_tests
  tests/pipeline_error_handling_test.cpp
)
target_link_libraries(pipeline_tests
  PRIVATE
    pipeline
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(pipeline_tests)
