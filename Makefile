BIN_NAME := main

SRC_PATH := src
INCLUDE_PATH := $(SRC_PATH)/include
BUILD_PATH := build
BIN_PATH := bin
LIB_PATH := lib

SRC_EXT := c

CC := gcc

COMPILE_FLAGS := -std=c99 -Wall -O0 -g #-Werror
LIB_FLAG = -L

SRC_FILE := $(wildcard $(SRC_PATH)/*.c)

LIB := $(patsubst %.$(SRC_EXT), %.a, $(SRC_FILE))
LIB := $(notdir $(LIB))
LIB := $(addprefix $(LIB_PATH)/lib, $(LIB))

LIB_CMPL := $(patsubst lib%.a, %, $(notdir $(LIB)))
LIB_CMPL := $(addprefix -l, $(LIB_CMPL))

OBJECTS := $(patsubst %.$(SRC_EXT), %.o, $(SRC_FILE))
OBJECTS := $(notdir $(OBJECTS))
OBJECTS := $(addprefix $(BUILD_PATH)/, $(OBJECTS))

.PHONY: all
all: dirs $(BIN_NAME)
# TestCompil

$(BIN_NAME): cost $(LIB)
	$(CC) $(COMPILE_FLAGS) $(LIB_FLAG)$(LIB_PATH) $(LIB_CMPL) -o $(BIN_PATH)/$(BIN_NAME)
# $(OBJECTS)
# $(CC) $(COMPILE_FLAGS) $^ -o $(BIN_PATH)/$@

.PHONY: cost
cost: $(OBJECTS)
	ar rcs lib/libPrintAll.a $(OBJECTS)
	ranlib lib/libPrintAll.a

$(LIB_PATH)/lib%.a: $(BUILD_PATH)/%.o
	ar rcs $@ $^
	ranlib $@

VPATH := $(INCLUDE_PATH)
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	$(CC) -MD $(COMPILE_FLAGS) $(addprefix -I, $(INCLUDE_PATH)) -c $< -o $@
include $(wildcard *.d)

.PHONY: dirs
dirs:
	@mkdir $(BIN_PATH) -p
	@mkdir $(BUILD_PATH) -p
	@mkdir $(LIB_PATH) -p

.PHONY: run
run:
	./$(BIN_PATH)/$(BIN_NAME)

.PHONY: clean
clean:
	@rm -rf $(BIN_PATH)
	@rm -rf $(BUILD_PATH)
	@rm -rf $(LIB_PATH)

.PHONY: testLib
testLib: $(LIB)
	@echo $(LIB)
	@echo $(notdir $(LIB))
	@echo $(patsubst lib%.a, %, $(notdir $(LIB)))
	@echo $(addprefix -l, $(patsubst lib%.a, %, $(notdir $(LIB))))