BIN_NAME := mySimpleComputer
#LIB_NAME := libmemory

SRC_PATH := src
BIN_PATH := bin
LIB_PATH := lib
BUILD_PATH := build

all: $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(BUILD_PATH)/main.o $(LIB_PATH)/libmemory.a $(LIB_PATH)/libterm.a $(LIB_PATH)/libbigchar.a $(BIN_PATH)
	gcc -Wall $< $(LIB_PATH)/libmemory.a $(LIB_PATH)/libterm.a $(LIB_PATH)/libbigchar.a -o $@

$(BUILD_PATH)/main.o: $(SRC_PATH)/main.c $(BUILD_PATH)
	gcc -Wall -c $< -o $@

$(LIB_PATH)/libmemory.a: $(BUILD_PATH)/memory.o $(LIB_PATH)
	ar rcs $@ $<

$(BUILD_PATH)/memory.o: $(SRC_PATH)/memory.c $(SRC_PATH)/memory.h $(BUILD_PATH)
	gcc -Wall -c $< -o $@

$(LIB_PATH)/libterm.a: $(BUILD_PATH)/myTerm.o $(LIB_PATH)
	ar rcs $@ $<

$(BUILD_PATH)/myTerm.o: $(SRC_PATH)/myTerm.c $(SRC_PATH)/myTerm.h $(BUILD_PATH)
	gcc -Wall -c $< -o $@

$(LIB_PATH)/libbigchar.a: $(BUILD_PATH)/myBigChars.o $(LIB_PATH)
	ar rcs $@ $<

$(BUILD_PATH)/myBigChars.o: $(SRC_PATH)/myBigChars.c $(SRC_PATH)/myBigChars.h $(BUILD_PATH)
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