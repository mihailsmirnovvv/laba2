CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
ASAN_FLAGS = -fsanitize=address

LIBS = -lm
TEST_LIBS = -lcunit

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects
EXEC_DIR = $(BUILD_DIR)/executables
TESTS_DIR = tests
SRC_DIR = src
INCLUDE_DIR = include

SOURCES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))  # Исключаем main.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TEST_SOURCES = $(wildcard $(TESTS_DIR)/test_*.c)
TEST_OBJECTS = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(TEST_SOURCES))

LIBRARY = $(BUILD_DIR)/matrix.a
TEST_EXEC = $(EXEC_DIR)/matrix_tests
RUN_EXEC = $(EXEC_DIR)/matrix_run

all: $(LIBRARY)

# Компиляция и запуск основного кода
run: clean $(LIBRARY)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(SRC_DIR)/main.c $(LIBRARY) -o $(RUN_EXEC) $(LIBS)
	./$(RUN_EXEC)

# Создание статической библиотеки без main.o
$(LIBRARY): $(BUILD_DIR) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

# Компиляция и запуск тестов
test: CFLAGS += -I$(INCLUDE_DIR)
test: $(LIBRARY) $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(LIBRARY)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(TEST_LIBS)

# Компиляция объектных файлов для тестов
$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Компиляция объектных файлов для библиотеки (без main.c)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Проверка утечек памяти с Valgrind
valgrind: $(TEST_EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

# Анализ кода cppcheck
cppcheck:
	cppcheck --enable=all --std=c11 -I$(INCLUDE_DIR) $(SOURCES) \
	--suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1

# Автоформатирование кода с clang-format
format:
	@clang-format -i $(wildcard src/*.c) $(wildcard include/*.h)

# Генерация документации Doxygen
docs:
	doxygen Doxyfile

# Очистка сборки
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test clean valgrind cppcheck format docs
