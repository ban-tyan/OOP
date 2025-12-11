# Makefile для проекта геометрических фигур
# Компилятор
CXX = g++
# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
# Флаги для документации Doxygen
DOXYGEN = doxygen

# Целевые исполняемые файлы
TARGET = geometric_figures
TEST_TARGET = test_figures

# Исходные файлы
SRCS = main.cpp figure.cpp polygon.cpp rectangle.cpp square.cpp
OBJS = $(SRCS:.cpp=.o)

# Тестовые файлы
TEST_SRCS = test.cpp figure.cpp polygon.cpp rectangle.cpp square.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Правило по умолчанию
all: $(TARGET) doc

# Сборка основной программы
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Сборка тестовой программы
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция .cpp файлов в .o файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Генерация документации Doxygen
doc:
	$(DOXYGEN) Doxyfile
	@echo "Документация сгенерирована в docs/html/"

# Генерация UML диаграммы
uml:
	plantuml diagram.puml
	@echo "UML диаграмма сгенерирована в diagram.png"

# Очистка
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
	rm -rf /html /latex
	rm -f diagram.png

# Запуск основной программы
run: $(TARGET)
	./$(TARGET)

# Показ справки
help:
	@echo "Доступные команды:"
	@echo "  make all     - собрать программу и документацию"
	@echo "  make         - то же, что и make all"
	@echo "  make run     - собрать и запустить программу"
	@echo "  make test    - собрать и запустить тесты"
	@echo "  make doc     - сгенерировать документацию Doxygen"
	@echo "  make uml     - сгенерировать UML диаграмму"
	@echo "  make clean   - очистить скомпилированные файлы"
	@echo "  make help    - показать эту справку"

# Зависимости заголовочных файлов
figure.o: figure.h drawable.h
polygon.o: polygon.h figure.h drawable.h
rectangle.o: rectangle.h polygon.h figure.h drawable.h
square.o: square.h rectangle.h polygon.h figure.h drawable.h
main.o: figure.h polygon.h rectangle.h square.h drawable.h
test.o: figure.h polygon.h rectangle.h square.h drawable.h

.PHONY: all clean doc uml run test help