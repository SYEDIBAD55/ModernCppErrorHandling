#include <gtest/gtest.h>
#include <fstream>
#include <expected>
#include <variant>
#include <filesystem>
#include <sstream>

// ========== Pipeline Declarations ==========
struct ConfigReadError { std::string filename; };
struct ConfigParseError { std::string line_content; int line_number; };
struct ValidationError { std::string field_name; std::string invalid_value; };
struct ProcessingError { std::string task_name; std::string details; };
using PipelineError = std::variant<ConfigReadError, ConfigParseError, ValidationError, ProcessingError>;

struct Config { std::string data; };
struct ValidatedData { std::string processed_data; };
struct Result { int final_result_code; };

std::expected<Config, PipelineError> LoadConfig(const std::string& filename);
std::expected<ValidatedData, PipelineError> ValidateData(const Config& config);
std::expected<Result, PipelineError> ProcessData(const ValidatedData& data);
// ========== End Pipeline Declarations ==========

// Helper for overloaded lambdas
template<class... Ts> struct Overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

TEST(PipelineTest, HandlesConfigReadError) {
    const std::string nonExistentFile = "non_existent_config_testfile.txt";
    
    // Ensure file doesn't exist
    ASSERT_FALSE(std::filesystem::exists(nonExistentFile)) 
        << "Test file unexpectedly exists: " << nonExistentFile;

    // Execute pipeline
    auto result = LoadConfig(nonExistentFile)
        .and_then(ValidateData)
        .and_then(ProcessData);

    // Verify error state
    ASSERT_FALSE(result.has_value()) 
        << "Expected error state but got success value";

    // Verify error type and content
    std::visit(Overloaded{
        [&](const ConfigReadError& e) {
            EXPECT_EQ(e.filename, nonExistentFile);
        },
        [](const auto& other) {
            FAIL() << "Expected ConfigReadError but got different error type";
        }
    }, result.error());
}

// ========== Pipeline Implementations ==========
std::expected<Config, PipelineError> LoadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::unexpected(ConfigReadError{filename});
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return Config{buffer.str()};
}

std::expected<ValidatedData, PipelineError> ValidateData(const Config& config) {
    if (config.data.find("invalid_field") != std::string::npos) {
        return std::unexpected(ValidationError{"invalid_field", "contains disallowed value"});
    }
    return ValidatedData{"Validated: " + config.data};
}

std::expected<Result, PipelineError> ProcessData(const ValidatedData& data) {
    if (data.processed_data.length() < 10) {
        return std::unexpected(ProcessingError{"Data Processing", "Input data too short for task"});
    }
    return Result{static_cast<int>(data.processed_data.length())};
}
// ========== End Pipeline Implementations ==========

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
