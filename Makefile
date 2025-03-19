# Compiler & options
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
ASAN_FLAGS = -fsanitize=address

# Libraries
LIBS = -lm
TEST_LIBS = -lcunit

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects
EXEC_DIR = $(BUILD_DIR)/executables
TESTS_DIR = tests
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_SOURCES = $(wildcard $(TESTS_DIR)/test_*.c)
TEST_OBJECTS = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(TEST_SOURCES))

# Targets
TARGET = $(BUILD_DIR)/matrix.a
TEST_EXEC = $(EXEC_DIR)/matrix_tests
RUN_EXEC = $(EXEC_DIR)/matrix_run

# Main targets
all: $(TARGET)

run: clean $(TARGET)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SRC_DIR)/main.c $(TARGET) -o $(RUN_EXEC) $(LIBS)
	./$(RUN_EXEC)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

# Test targets
test: CFLAGS += -I$(INCLUDE_DIR)
test: $(TARGET) $(TEST_EXEC)
	./$(TEST_EXEC)

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

cppcheck:
	cppcheck --enable=all --std=c11 -I$(INCLUDE_DIR) $(SOURCES) \
	--suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1

format:
	@clang-format -i $(wildcard src/*.c) $(wildcard include/*.h)

docs:
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test clean valgrind cppcheck format docs

