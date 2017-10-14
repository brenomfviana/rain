# Directories
SRC_DIR   := ./src
BUILD_DIR := ./build
INC_DIRS  := ./include ./utils
# Flags
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPP_FLAGS := -std=c++11 -Wall -Wextra -g -pthread $(INC_FLAGS) -O2 -MMD -MP
# Objects
SRCS := $(shell cd $(SRC_DIR); find . -name "*.cpp")
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRCS)))
DEPS := $(OBJS:.o=.d)
# Make
rain: $(OBJS)
	g++ $(CPP_FLAGS) $(OBJS) -o $@
$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	g++ $(CPP_FLAGS) -c $(INCLUDES) $< -o $@
# Clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean

-include $(DEPS)
