# Modern C++ Error Handling Assignment

This repository demonstrates modern C++ error handling using:
- `std::expected` (C++23)
- `std::variant` (C++17)
- `std::visit` (C++17)

## Building and Running Tests

### Prerequisites
- CMake (version 3.14 or higher)
- C++23 compatible compiler (GCC 13+, Clang 16+, MSVC 19.30+)
- Git

### Build Steps
```bash
# Clone repository
git clone https://github.com/SYEDIBAD55/ModernCppErrorHandling.git
cd ModernCppErrorHandling

# Configure build
cmake -B build -S .

# Compile tests
cmake --build build

# Run tests (from build directory)
cd build && ./pipeline_tests
```

### Test Description
The unit test `HandlesConfigReadError` verifies:
1. File read errors are properly detected
2. Errors propagate through the pipeline
3. Correct error type is returned (`ConfigReadError`)
4. Error contains accurate contextual data (filename)

## Assignment Requirements Met
- Comprehensive unit test for specific error scenario
- Uses GoogleTest framework
- Verifies error propagation through `and_then` chain
- Checks error type and content using `std::visit`
- Clean code with proper error handling
