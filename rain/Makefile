# Language
CXX = g++
# Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pthread
# Executable
TARGET = rain
# Header's inclusion
INCLUDES = -I ./include
# Binary directory
BIN_DIR = ./bin
# Source
SRC = ./src
# Get all cpp files
CPP_SRC = $(wildcard $(SRC)/*.cpp)
# All objects
OBJS = $(addprefix $(BIN_DIR)/,$(notdir $(CPP_SRC:.cpp=.o)))
# Make
all: clean create-bin-folder $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)
$(BIN_DIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) ./$< -o ./$@
# Clean
clean:
	rm -rf $(BIN_DIR)
# Create bin folder
create-bin-folder:
	mkdir bin
.PHONY: all clean
