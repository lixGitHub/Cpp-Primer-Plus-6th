#####################
# Makefile
#####################

# Define the target name
TARGET := print

# Directory to store the compiled binary
BUILD_DIR := bin

# Compiler settings
CC     := gcc
CXX    := g++
LIBS   :=      # Add any libraries here, e.g. -lm for math
LDFLAGS :=     # Add linker flags here
DEFINES :=     # Add preprocessor defines here
INCLUDE := -I. # Include the current directory

# Compiler flags (currently unused)
CFLAGS  :=     # C compiler flags (add optimization or warnings here)
CXXFLAGS :=    # C++ compiler flags (add optimization or warnings here)

# All target to build
all: $(BUILD_DIR)/$(TARGET)

# Rule for building the target `print` in the `build` folder
$(BUILD_DIR)/$(TARGET): print.cpp
	@mkdir -p $(BUILD_DIR)  # Ensure the build directory exists
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) $(LDFLAGS)

# Optional: Add object file compilation if needed
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $(BUILD_DIR)/$@

.PHONY: clean cleanobj

# Clean up build artifacts
clean:
	rm -f $(BUILD_DIR)/$(TARGET)

# Clean up object files
cleanobj:
	rm -f $(BUILD_DIR)/*.o
