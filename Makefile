# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# Directories
SRC_DIR = src
TEST_DIR = test
INCLUDE_DIR = include
BUILD_DIR = build

# Google Test paths
GTEST_DIR = third_party/googletest/googletest
GTEST_INCLUDE = $(GTEST_DIR)/include
GTEST_SRC = $(GTEST_DIR)/src

# Include paths
INCLUDES = -I$(INCLUDE_DIR) -I$(GTEST_INCLUDE) -I$(GTEST_DIR)

# Google Test library
GTEST_LIB = $(BUILD_DIR)/libgtest.a

# Source files and objects
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Test sources and target
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_TARGET = $(BUILD_DIR)/run_tests

# Default target
all: $(BUILD_DIR) $(SRC_OBJS)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build source files as object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build Google Test library (gtest-all.cc contains everything)
$(BUILD_DIR)/gtest-all.o: $(GTEST_SRC)/gtest-all.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -I$(GTEST_DIR) -c $< -o $@

$(BUILD_DIR)/gtest_main.o: $(GTEST_SRC)/gtest_main.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_INCLUDE) -I$(GTEST_DIR) -c $< -o $@

$(GTEST_LIB): $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	ar rcs $@ $^

# Build and run tests
test: $(BUILD_DIR) $(GTEST_LIB) $(SRC_OBJS) $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_SRCS) $(SRC_OBJS) $(GTEST_LIB) -o $(TEST_TARGET)
	./$(TEST_TARGET)

# Run tests only (assumes already built)
run_tests: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Rebuild everything
rebuild: clean all

.PHONY: all test run_tests clean rebuild