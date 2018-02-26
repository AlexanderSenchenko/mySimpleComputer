BIN_NAME := memory
LIB_NAME := libmemory

SRC_PATH := src
BIN_PATH := bin
LIB_PATH := ~/mylib
BUILD_PATH := build

all: $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(BUILD_PATH)/main.o $(LIB_PATH)/$(LIB_NAME).a $(BIN_PATH)
	gcc -Wall $< $(LIB_PATH)/$(LIB_NAME).a -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(SRC_PATH)/memory.h $(BUILD_PATH)
	gcc -Wall -c $< -o $@

$(LIB_PATH)/libmemory.a: $(BUILD_PATH)/memory.o $(LIB_PATH)
	ar rcs $@ $<

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c $(SRC_PATH)/%.h $(BUILD_PATH)
	gcc -Wall -c $< -o $@

#-include &(wildcard *.d)

$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

$(LIB_PATH):
	@mkdir -p $(LIB_PATH)

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)
	rm -rf $(BIN_PATH)

.PHONY: clean_lib
clean_lib:
	rm -rf $(LIB_PATH)/$(LIB_NAME).a