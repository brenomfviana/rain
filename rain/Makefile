# Language
CXX = g++ -pthread
# Flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g
# Executable
TARGET = rain
# Header's inclusion
INCLUDES = -I ./include
# Binary directory
BIN_DIR = ./bin
# Source
SRC = ./src

CPP_SRC = $(wildcard $(SRC)/*.cpp)

OBJS = $(addprefix $(BIN_DIR)/,$(notdir $(CPP_SRC:.cpp=.o)))

all: clean create-bin-folder $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) ./$< -o ./$@

clean:
	rm -rf $(BIN_DIR)
create-bin-folder:
	mkdir bin
.PHONY: all clean
