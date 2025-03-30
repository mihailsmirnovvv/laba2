CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
ASAN_FLAGS = -fsanitize=address

LIBS = -lm
TEST_LIBS = -lcunit

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects
EXEC_DIR = $(BUILD_DIR)/executables
SRC_DIR = src
INCLUDE_DIR = include
TESTS_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
OBJECTS := $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS))

LIBRARY = $(BUILD_DIR)/matrix.a
RUN_EXEC = $(EXEC_DIR)/matrix_run
TEST_EXEC = $(EXEC_DIR)/matrix_tests

all: $(LIBRARY)

$(LIBRARY): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

run: clean $(LIBRARY) $(OBJ_DIR)/main.o | $(EXEC_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/main.o $(LIBRARY) -o $(RUN_EXEC) $(LIBS)
	./$(RUN_EXEC)

test: CFLAGS += -I$(INCLUDE_DIR)
test: $(LIBRARY) $(OBJ_DIR)/test_matrix.o | $(EXEC_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/test_matrix.o $(LIBRARY) -o $(TEST_EXEC) $(LIBS) $(TEST_LIBS)
	./$(TEST_EXEC)

$(OBJ_DIR)/test_matrix.o: $(TESTS_DIR)/test_matrix.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR) $(EXEC_DIR):
	@mkdir -p $@

valgrind: $(TEST_EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

cppcheck:
	cppcheck --enable=all --std=c11 -I$(INCLUDE_DIR) $(SOURCES) --suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1

format:
	@clang-format -i $(wildcard src/*.c) $(wildcard include/*.h)

docs:
	doxygen docs/Doxyfile

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test clean valgrind cppcheck format docs