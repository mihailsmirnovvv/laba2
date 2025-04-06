CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
ASAN_FLAGS = -fsanitize=address -g

LIBS = -lm
TEST_LIBS = -lcunit

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects
EXEC_DIR = $(BUILD_DIR)/executables
TESTS_DIR = tests
SRC_DIR = src
SRC_DIRS = $(SRC_DIR)/matrix $(SRC_DIR)/output
INCLUDE_DIR = include

SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_SOURCES = $(TESTS_DIR)/all_tests.c
TEST_OBJECTS = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(TEST_SOURCES))

TARGET = $(BUILD_DIR)/matrix.a
TEST_EXEC = $(EXEC_DIR)/matrix_tests

all: $(TARGET)

main: clean $(TARGET)
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(TARGET) -o main $(LIBS)
	./main
	@rm main

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

test: CFLAGS += -I$(INCLUDE_DIR)
test: $(TARGET) $(TEST_EXEC)
	./$(TEST_EXEC)
	@rm -f test_matrix.txt

$(TEST_EXEC): $(TEST_OBJECTS) $(TARGET)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(TEST_LIBS)

$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

valgrind: $(TEST_EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)
	@rm -f $(TEST_EXEC) test_matrix.txt

cppcheck:
	cppcheck --enable=all --std=c11 -I$(INCLUDE_DIR) $(SOURCES) \
	--suppress=missingIncludeSystem --suppress=unusedFunction --suppress=checkersReport --error-exitcode=1

format:
	@clang-format -i $$(find . -name "*.c")
	@clang-format -i $$(find . -name "*.h")

docs:
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean valgrind cppcheck docs

