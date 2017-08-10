# Language
CXX = g++
# Flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g
# Executable
TARGET = render
# Header's inclusion
INCLUDES = -I ./include ./utility
# Binary directory
BIN_DIR = ./bin
# Source
SRC = ./src

CPP_SRC = $(wildcard $(SRC)/*.cpp)

OBJS = $(addprefix $(BIN_DIR)/,$(notdir $(CPP_SRC:.cpp=.o)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) ./$< -o ./$@

clean:
	rm -f $(BIN_DIR)/$(TARGET) $(BIN_DIR)/*.o
.PHONY: all clean