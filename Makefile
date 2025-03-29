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

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Исключаем main.o, чтобы он не попал в библиотеку
OBJECTS := $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS))

LIBRARY = $(BUILD_DIR)/matrix.a
TEST_EXEC = $(EXEC_DIR)/matrix_tests
RUN_EXEC = $(EXEC_DIR)/matrix_run

all: $(LIBRARY)

$(LIBRARY): $(BUILD_DIR) $(OBJECTS)
	@mkdir -p $(dir $@)
	ar -rcs $@ $(OBJECTS)

run: clean $(LIBRARY) $(OBJ_DIR)/main.o
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(OBJ_DIR)/main.c $(LIBRARY) -o $(RUN_EXEC) $(LIBS)
	./$(RUN_EXEC)

# Компиляция объектов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Создание папки build
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Запуск тестов
test: CFLAGS += -I$(INCLUDE_DIR)
test: $(LIBRARY) $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(LIBRARY)
	@mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJECTS) $(LIBRARY) -o $@ $(LIBS) $(TEST_LIBS)

$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Проверка утечек памяти
valgrind: $(TEST_EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)

# Анализ кода
cppcheck:
	cppcheck --enable=all --std=c11 -I$(INCLUDE_DIR) $(SOURCES) \
	--suppress=missingIncludeSystem --suppress=unusedFunction --error-exitcode=1

# Форматирование кода
format:
	@clang-format -i $(wildcard src/*.c) $(wildcard include/*.h)

# Генерация документации
docs:
	doxygen Doxyfile

# Очистка
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test clean valgrind cppcheck format docs