# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -Isrc

# Directories
SRC_DIR := src
TEST_DIR := test
OBJ_DIR := obj
BUILD_DIR := build
BUILD_TEST_DIR := $(BUILD_DIR)/test

# Files
MAIN_SRC := main.cpp
MAIN_OBJ := $(OBJ_DIR)/main.o
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.test.o, $(TEST_FILES))

# Test executables (named after test sources)
TEST_EXES := $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_TEST_DIR)/%, $(TEST_FILES))

# Main executable
TARGET := $(BUILD_DIR)/main

# Default target
all: $(TARGET) $(TEST_EXES)

# Main program build
$(TARGET): $(OBJ_FILES) $(MAIN_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@

# Compile main.cpp separately
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test executable build (excluding main.o)
$(BUILD_TEST_DIR)/%: $(TEST_DIR)/%.cpp $(filter-out $(MAIN_OBJ), $(OBJ_FILES))
	@mkdir -p $(BUILD_TEST_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJ_DIR)/$*.test.o
	$(CXX) $(filter-out $(MAIN_OBJ), $(OBJ_FILES)) $(OBJ_DIR)/$*.test.o -o $@

# Compile other source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean
