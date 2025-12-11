/**
 * @file main.cpp
 * @brief Комплексное тестирование иерархии классов геометрических фигур
 * @mainpage Демонстрация иерархии классов геометрических фигур
 * 
 * Этот проект демонстрирует:
 * 1. Иерархию наследования: Drawable ← Figure ← Polygon ← Rectangle ← Square
 * 2. Множественное наследование (Drawable интерфейс)
 * 3. Полиморфизм через указатели на базовый класс
 * 4. Глубокое копирование
 * 5. Статические члены класса
 * 6. Виртуальные функции с реализацией по умолчанию
 * 7. Обработку исключений
 * 8. Невозможность создания объектов абстрактных классов
 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <typeinfo>
#include "figure.h"
#include "polygon.h"
#include "rectangle.h"
#include "square.h"

// ===================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ ТЕСТИРОВАНИЯ
// ===================================================================

/**
 * @brief Функция демонстрации полиморфизма через указатели
 * @param figure Указатель на базовый класс
 */
void demonstratePolymorphismViaPointer(Figure* figure) {
    if (!figure) return;
    
    std::cout << "  Через указатель Figure*:" << std::endl;
    std::cout << "    getInfo(): " << figure->getInfo() << std::endl;
    std::cout << "    area(): " << figure->area() << std::endl;
    std::cout << "    draw(): ";
    figure->draw();
}

/**
 * @brief Функция демонстрации полиморфизма через ссылки
 * @param figure Ссылка на базовый класс
 */
void demonstratePolymorphismViaReference(Figure& figure) {
    std::cout << "  Через ссылку Figure&:" << std::endl;
    std::cout << "    getInfo(): " << figure.getInfo() << std::endl;
    std::cout << "    area(): " << figure.area() << std::endl;
    std::cout << "    draw(): ";
    figure.draw();
}

/**
 * @brief Тест создания объектов всех возможных типов
 */
void testAllObjectTypesCreation() {
    std::cout << "\n=== Тест 1: Создание объектов всех возможных типов ===" << std::endl;
    
    std::cout << "1.1. Создание Polygon (треугольник):" << std::endl;
    Point trianglePoints[3] = {Point(0, 0), Point(4, 0), Point(2, 3)};
    Polygon triangle("Triangle", 3, trianglePoints);
    std::cout << "    Успешно создан: " << triangle.getInfo() << std::endl;
    assert(triangle.getVerticesCount() == 3);
    
    std::cout << "\n1.2. Создание Polygon (четырехугольник):" << std::endl;
    Point quadPoints[4] = {Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)};
    Polygon quadrilateral("Quadrilateral", 4, quadPoints);
    std::cout << "    Успешно создан: " << quadrilateral.getInfo() << std::endl;
    
    std::cout << "\n1.3. Создание Rectangle:" << std::endl;
    Rectangle rectangle("My Rectangle", 5.0, 3.0, 10, 10);
    std::cout << "    Успешно создан: " << rectangle.getInfo() << std::endl;
    assert(rectangle.getWidth() == 5.0);
    assert(rectangle.getHeight() == 3.0);
    
    std::cout << "\n1.4. Создание Square:" << std::endl;
    Square square("My Square", 4.0, 20, 20);
    std::cout << "    Успешно создан: " << square.getInfo() << std::endl;
    assert(square.getSide() == 4.0);
    assert(square.isSquare());
    
    std::cout << "\n1.5. Создание пустого Polygon:" << std::endl;
    Polygon emptyPolygon("Empty Polygon");
    std::cout << "    Успешно создан: " << emptyPolygon.getInfo() << std::endl;
    assert(emptyPolygon.getVerticesCount() == 0);
    
    std::cout << "\n✓ Все конкретные типы успешно созданы!" << std::endl;
    
    // ===================================================================
    // ВАЖНО: Демонстрация, что нельзя создать объект абстрактного класса
    // ===================================================================
    std::cout << "\n1.6. Попытка создать объект абстрактного класса Figure:" << std::endl;
    std::cout << "    КОМПИЛЯТОР НЕ ПОЗВОЛИТ: Figure abstractFigure(\"Abstract\");" << std::endl;
    std::cout << "    Причина: Figure содержит чисто виртуальные функции area() и draw()" << std::endl;
    std::cout << "    Это корректное поведение - абстрактные классы не могут быть инстанциированы." << std::endl;
    
    // Раскомментируйте для проверки ошибки компиляции:
    /*
    Figure abstractFigure("Abstract"); // ОШИБКА КОМПИЛЯЦИИ: cannot declare variable 'abstractFigure' 
                                       // to be of abstract type 'Figure'
    */
}

/**
 * @brief Тест полиморфизма через указатели и ссылки разных типов
 */
void testPolymorphism() {
    std::cout << "\n=== Тест 2: Полиморфизм через указатели и ссылки ===" << std::endl;
    
    // Создаем массив указателей на базовый класс
    const int NUM_FIGURES = 5;
    Figure* figures[NUM_FIGURES];
    
    // Инициализация разными типами
    Point hexagonPoints[6];
    for (int i = 0; i < 6; i++) {
        double angle = 2 * M_PI * i / 6;
        hexagonPoints[i] = Point(std::cos(angle) * 2, std::sin(angle) * 2);
    }
    
    figures[0] = new Polygon("Hexagon", 6, hexagonPoints);
    figures[1] = new Rectangle("Rect 1", 8.0, 4.0);
    figures[2] = new Square("Square 1", 5.0);
    figures[3] = new Rectangle("Rect 2", 6.0, 6.0);  // Квадрат, но тип Rectangle
    figures[4] = new Square("Square 2", 7.0);
    
    std::cout << "2.1. Полиморфный вызов через указатели Figure*:" << std::endl;
    double totalArea = 0;
    for (int i = 0; i < NUM_FIGURES; i++) {
        std::cout << "  Фигура " << i+1 << " (" << figures[i]->getName() << "):" << std::endl;
        demonstratePolymorphismViaPointer(figures[i]);
        totalArea += figures[i]->area();
        std::cout << std::endl;
    }
    
    std::cout << "\n2.2. Полиморфный вызов через ссылки Figure&:" << std::endl;
    for (int i = 0; i < NUM_FIGURES; i++) {
        std::cout << "  Фигура " << i+1 << " через ссылку:" << std::endl;
        demonstratePolymorphismViaReference(*figures[i]);
        std::cout << std::endl;
    }
    
    std::cout << "\n2.3. Определение реального типа через typeid и dynamic_cast:" << std::endl;
    for (int i = 0; i < NUM_FIGURES; i++) {
        std::cout << "  Фигура " << i+1 << " - typeid: " << typeid(*figures[i]).name();
        
        // Попытка dynamic_cast к различным типам
        if (Square* s = dynamic_cast<Square*>(figures[i])) {
            std::cout << " (это Square, сторона = " << s->getSide() << ")";
        } else if (Rectangle* r = dynamic_cast<Rectangle*>(figures[i])) {
            std::cout << " (это Rectangle, " << r->getWidth() << "x" << r->getHeight() << ")";
            if (r->isSquare()) {
                std::cout << " [является квадратом]";
            }
        } else if (Polygon* p = dynamic_cast<Polygon*>(figures[i])) {
            std::cout << " (это Polygon, вершин: " << p->getVerticesCount() << ")";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n2.4. Хранение в массиве Drawable* (множественное наследование):" << std::endl;
    Drawable* drawables[NUM_FIGURES];
    for (int i = 0; i < NUM_FIGURES; i++) {
        drawables[i] = figures[i];  // Безопасное преобразование Figure* → Drawable*
        std::cout << "  Drawable[" << i << "].draw(): ";
        drawables[i]->draw();
    }
    
    // Очистка
    for (int i = 0; i < NUM_FIGURES; i++) {
        delete figures[i];
    }
    
    std::cout << "\n✓ Полиморфизм работает корректно!" << std::endl;
}

/**
 * @brief Тест статических членов класса в различных сценариях
 */
void testStaticMembers() {
    std::cout << "\n=== Тест 3: Статические члены класса ===" << std::endl;
    
    int initialCount = Figure::getFigureCount();
    std::cout << "3.1. Начальное количество фигур: " << initialCount << std::endl;
    
    std::cout << "\n3.2. Создание фигур в разных областях видимости:" << std::endl;
    
    // Область видимости 1
    {
        std::cout << "  Область видимости 1:" << std::endl;
        Rectangle r1("Scope1 Rect1", 2, 3);
        Square s1("Scope1 Square1", 4);
        std::cout << "    Создано 2 фигуры, текущий счетчик: " << Figure::getFigureCount() << std::endl;
        assert(Figure::getFigureCount() == initialCount + 2);
    }
    std::cout << "  После выхода из области видимости 1: " << Figure::getFigureCount() << std::endl;
    assert(Figure::getFigureCount() == initialCount);
    
    // Область видимости 2
    {
        std::cout << "\n  Область видимости 2 (динамическое выделение):" << std::endl;
        Figure* dynamicFigures[3];
        dynamicFigures[0] = new Rectangle("Dyn Rect", 5, 5);
        dynamicFigures[1] = new Square("Dyn Square", 6);
        dynamicFigures[2] = new Rectangle("Dyn Rect2", 7, 3);
        
        std::cout << "    Создано 3 фигуры динамически, текущий счетчик: " << Figure::getFigureCount() << std::endl;
        assert(Figure::getFigureCount() == initialCount + 3);
        
        // Удаление вручную
        for (int i = 0; i < 3; i++) {
            delete dynamicFigures[i];
        }
        std::cout << "    После удаления динамических фигур: " << Figure::getFigureCount() << std::endl;
        assert(Figure::getFigureCount() == initialCount);
    }
    
    std::cout << "\n3.3. Расчет средней площади:" << std::endl;
    
    // Создаем несколько фигур для расчета средней площади
    Figure* testFigures[4];
    testFigures[0] = new Rectangle("Test1", 10, 5);    // Площадь 50
    testFigures[1] = new Square("Test2", 4);           // Площадь 16
    testFigures[2] = new Rectangle("Test3", 3, 7);     // Площадь 21
    testFigures[3] = new Square("Test4", 6);           // Площадь 36
    
    double totalArea = 0;
    for (int i = 0; i < 4; i++) {
        totalArea += testFigures[i]->area();
    }
    
    double calculatedAvg = totalArea / 4;
    double staticAvg = Figure::getAverageArea(totalArea);
    
    std::cout << "  Общая площадь: " << totalArea << std::endl;
    std::cout << "  Количество фигур: " << Figure::getFigureCount() << std::endl;
    std::cout << "  Средняя площадь (ручной расчет): " << calculatedAvg << std::endl;
    std::cout << "  Средняя площадь (статический метод): " << staticAvg << std::endl;
    
    // Допустимая погрешность для сравнения double
    assert(std::abs(calculatedAvg - staticAvg) < 0.0001);
    
    // Тест при нулевом количестве фигур
    {
        double zeroArea = 0;
        double avgForZero = Figure::getAverageArea(zeroArea);
        std::cout << "\n3.4. Средняя площадь при нуле фигур: " << avgForZero << std::endl;
        assert(avgForZero == 0.0);
    }
    
    // Очистка
    for (int i = 0; i < 4; i++) {
        delete testFigures[i];
    }
    
    std::cout << "\n✓ Статические члены работают корректно!" << std::endl;
}

/**
 * @brief Тест глубокого копирования для всех классов
 */
void testDeepCopy() {
    std::cout << "\n=== Тест 4: Глубокое копирование ===" << std::endl;
    
    std::cout << "4.1. Глубокое копирование для Polygon:" << std::endl;
    {
        Point points[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
        Polygon original("Original Polygon", 4, points);
        
        // Конструктор копирования
        Polygon copyByConstructor(original);
        
        // Оператор присваивания
        Polygon copyByAssignment("Empty", 0, nullptr);
        copyByAssignment = original;
        
        std::cout << "  Оригинал: " << original.getInfo() << std::endl;
        std::cout << "  Копия (конструктор): " << copyByConstructor.getInfo() << std::endl;
        std::cout << "  Копия (присваивание): " << copyByAssignment.getInfo() << std::endl;
        
        // Модифицируем оригинал
        Point newPoints[3] = {Point(0, 0), Point(3, 0), Point(1.5, 2.6)};
        original.setVertices(3, newPoints);
        
        std::cout << "  После модификации оригинала:" << std::endl;
        std::cout << "  Оригинал: " << original.getInfo() << std::endl;
        std::cout << "  Копия (конструктор): " << copyByConstructor.getInfo() << std::endl;
        std::cout << "  Копия (присваивание): " << copyByAssignment.getInfo() << std::endl;
        
        // Проверка независимости копий
        assert(copyByConstructor.getVerticesCount() == 4);
        assert(copyByAssignment.getVerticesCount() == 4);
        assert(original.getVerticesCount() == 3);
        std::cout << "  ✓ Копии Polygon независимы" << std::endl;
    }
    
    std::cout << "\n4.2. Глубокое копирование для Rectangle:" << std::endl;
    {
        Rectangle original("Original Rectangle", 8.0, 6.0, 5, 5);
        
        Rectangle copy1 = original;  // Конструктор копирования
        Rectangle copy2("Temp", 1, 1);
        copy2 = original;  // Оператор присваивания
        
        // Проверка до модификации
        assert(copy1.getWidth() == 8.0);
        assert(copy2.getWidth() == 8.0);
        
        // Модифицируем оригинал
        original.setDimensions(12.0, 9.0);
        
        // Проверка после модификации
        assert(copy1.getWidth() == 8.0);
        assert(copy2.getWidth() == 8.0);
        assert(original.getWidth() == 12.0);
        
        std::cout << "  Оригинал изменен: " << original.getInfo() << std::endl;
        std::cout << "  Копия 1 остается: " << copy1.getInfo() << std::endl;
        std::cout << "  Копия 2 остается: " << copy2.getInfo() << std::endl;
        std::cout << "  ✓ Копии Rectangle независимы" << std::endl;
    }
    
    std::cout << "\n4.3. Глубокое копирование для Square:" << std::endl;
    {
        Square original("Original Square", 10.0, 0, 0);
        
        Square copy1 = original;
        Square copy2("Temp", 2);
        copy2 = original;
        
        // Проверка до модификации
        assert(copy1.getSide() == 10.0);
        assert(copy2.getSide() == 10.0);
        
        // Модифицируем оригинал
        original.setSide(15.0);
        
        // Проверка после модификации
        assert(copy1.getSide() == 10.0);
        assert(copy2.getSide() == 10.0);
        assert(original.getSide() == 15.0);
        
        std::cout << "  Оригинал изменен: " << original.getInfo() << std::endl;
        std::cout << "  Копия 1 остается: " << copy1.getInfo() << std::endl;
        std::cout << "  Копия 2 остается: " << copy2.getInfo() << std::endl;
        std::cout << "  ✓ Копии Square независимы" << std::endl;
    }
    
    std::cout << "\n4.4. Тест самоприсваивания:" << std::endl;
    {
        Rectangle rect("Self-Assign Test", 7, 5);
        Rectangle& rectRef = rect;
        rect = rectRef;  // Самоприсваивание
        
        // Проверяем, что объект не сломался
        assert(rect.getWidth() == 7.0);
        assert(rect.getHeight() == 5.0);
        std::cout << "  ✓ Самоприсваивание работает безопасно" << std::endl;
    }
    
    std::cout << "\n✓ Глубокое копирование работает корректно для всех классов!" << std::endl;
}

/**
 * @brief Тест виртуальных функций с реализацией по умолчанию
 */
void testVirtualFunctionsWithDefault() {
    std::cout << "\n=== Тест 5: Виртуальные функции с реализацией по умолчанию ===" << std::endl;
    
    std::cout << "5.1. Создание объектов разных типов:" << std::endl;
    Polygon polygon("Generic Polygon");
    Rectangle rectangle("My Rectangle", 5, 3);
    Square square("My Square", 4);
    
    std::cout << "\n5.2. Вызов setFillColor() - виртуальная функция:" << std::endl;
    std::cout << "  Polygon::setFillColor(): ";
    polygon.setFillColor("gray");
    
    std::cout << "  Rectangle::setFillColor(): ";
    rectangle.setFillColor("blue");
    
    std::cout << "  Square::setFillColor(): ";
    square.setFillColor("green");
    
    std::cout << "\n5.3. Вызов через указатели на базовый класс:" << std::endl;
    Figure* figures[3] = {&polygon, &rectangle, &square};
    
    for (int i = 0; i < 3; i++) {
        std::cout << "  Фигура " << i+1 << " (" << figures[i]->getName() << "): ";
        
        // Не можем вызвать setFillColor() через Figure*, т.к. она не объявлена в Figure
        // Это демонстрирует ограничения при работе через указатели на базовый класс
        std::cout << "area() = " << figures[i]->area();
        
        // Но можем использовать dynamic_cast для доступа к методам производных классов
        if (Polygon* p = dynamic_cast<Polygon*>(figures[i])) {
            std::cout << ", может быть преобразована к Polygon*";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n✓ Виртуальные функции с реализацией по умолчанию работают корректно!" << std::endl;
}

/**
 * @brief Тест множественного наследования
 */
void testMultipleInheritance() {
    std::cout << "\n=== Тест 6: Множественное наследование ===" << std::endl;
    
    Square square("Multiple Inheritance Square", 6.0, 10, 10);
    
    std::cout << "6.1. Доступ к объекту через указатели разных типов:" << std::endl;
    
    // Создаем указатели всех возможных типов на один объект
    Square* squarePtr = &square;
    Rectangle* rectPtr = &square;
    Polygon* polyPtr = &square;
    Figure* figurePtr = &square;
    Drawable* drawablePtr = &square;
    
    std::cout << "  Square*:       " << squarePtr->getInfo() << std::endl;
    std::cout << "  Rectangle*:    " << rectPtr->getInfo() << std::endl;
    std::cout << "  Polygon*:      " << polyPtr->getInfo() << std::endl;
    std::cout << "  Figure*:       " << figurePtr->getInfo() << std::endl;
    
    // Для Drawable* нет метода getInfo(), но можно вызвать draw()
    std::cout << "  Drawable*:     ";
    drawablePtr->draw();
    
    std::cout << "\n6.2. Проверка преобразований между типами:" << std::endl;
    
    // Восходящее преобразование (upcast) - безопасно
    Figure* fromSquare = squarePtr;  // Square* → Figure*
    std::cout << "  Square* → Figure*: безопасно, area = " << fromSquare->area() << std::endl;
    
    // Нисходящее преобразование (downcast) - требует dynamic_cast
    Square* backToSquare = dynamic_cast<Square*>(figurePtr);
    if (backToSquare) {
        std::cout << "  Figure* → Square*: успешно через dynamic_cast" << std::endl;
    }
    
    // Попытка преобразования к неправильному типу
    Rectangle* rectFromPoly = dynamic_cast<Rectangle*>(polyPtr);
    if (rectFromPoly) {
        std::cout << "  Polygon* → Rectangle*: успешно (ожидаемо для Square)" << std::endl;
    }
    
    // Преобразование через множественное наследование
    Drawable* fromFigure = figurePtr;  // Figure* → Drawable* (множественное наследование)
    std::cout << "  Figure* → Drawable*: успешно (множественное наследование)" << std::endl;
    
    std::cout << "\n6.3. Таблица виртуальных методов (vtable) проверка:" << std::endl;
    std::cout << "  Вызов draw() через разные указатели:" << std::endl;
    std::cout << "    squarePtr->draw():   ";
    squarePtr->draw();
    std::cout << "    rectPtr->draw():     ";
    rectPtr->draw();
    std::cout << "    figurePtr->draw():   ";
    figurePtr->draw();
    std::cout << "    drawablePtr->draw(): ";
    drawablePtr->draw();
    
    std::cout << "\n✓ Множественное наследование работает корректно!" << std::endl;
}

/**
 * @brief Тест обработки исключений
 */
void testExceptionHandling() {
    std::cout << "\n=== Тест 7: Обработка исключений ===" << std::endl;
    
    std::cout << "7.1. Исключения при создании объектов:" << std::endl;
    
    // Некорректный Rectangle
    try {
        std::cout << "  Попытка создать Rectangle с шириной -5: ";
        Rectangle invalidRect("Invalid", -5.0, 10.0);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    // Некорректный Square
    try {
        std::cout << "  Попытка создать Square с стороной 0: ";
        Square invalidSquare("Invalid", 0.0);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    // Некорректный Polygon (слишком мало вершин)
    try {
        std::cout << "  Попытка создать Polygon с 2 вершинами: ";
        Point twoPoints[2] = {Point(0, 0), Point(1, 0)};
        Polygon invalidPoly("Invalid", 2, twoPoints);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::cout << "\n7.2. Исключения при модификации объектов:" << std::endl;
    
    // Некорректное изменение размеров Rectangle
    try {
        std::cout << "  Попытка setDimensions(-1, 5): ";
        Rectangle rect("Test", 5, 5);
        rect.setDimensions(-1.0, 5.0);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    // Некорректное изменение стороны Square
    try {
        std::cout << "  Попытка setSide(-2): ";
        Square square("Test", 5);
        square.setSide(-2.0);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    // Исключение при доступе к несуществующей вершине
    try {
        std::cout << "  Попытка getVertex(10) у Polygon с 3 вершинами: ";
        Polygon poly("Triangle", 3);
        Point p = poly.getVertex(10);
        std::cout << "ОШИБКА: Исключение не было выброшено!" << std::endl;
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "✓ Поймано исключение: " << e.what() << std::endl;
    }
    
    std::cout << "\n7.3. Исключения при работе с nullptr:" << std::endl;
    
    // Безопасная работа с указателями
    Figure* nullFigure = nullptr;
    if (nullFigure) {
        nullFigure->draw();  // Не выполнится
        assert(false);
    } else {
        std::cout << "  Проверка на nullptr предотвращает вызов метода на нулевом указателе" << std::endl;
    }
    
    std::cout << "\n✓ Обработка исключений работает корректно!" << std::endl;
}

/**
 * @brief Тест жизненного цикла объектов
 */
void testObjectLifetime() {
    std::cout << "\n=== Тест 8: Жизненный цикл объектов ===" << std::endl;
    
    std::cout << "8.1. Создание и уничтожение в стеке:" << std::endl;
    {
        Rectangle stackRect("Stack Rectangle", 4, 3);
        Square stackSquare("Stack Square", 5);
        std::cout << "  В области видимости: " << Figure::getFigureCount() << " фигур" << std::endl;
    }
    std::cout << "  После выхода из области видимости: " << Figure::getFigureCount() << " фигур" << std::endl;
    
    std::cout << "\n8.2. Создание и уничтожение в куче:" << std::endl;
    int beforeHeap = Figure::getFigureCount();
    Rectangle* heapRect = new Rectangle("Heap Rectangle", 6, 4);
    Square* heapSquare = new Square("Heap Square", 7);
    std::cout << "  После new: " << Figure::getFigureCount() << " фигур" << std::endl;
    
    delete heapRect;
    delete heapSquare;
    std::cout << "  После delete: " << Figure::getFigureCount() << " фигур" << std::endl;
    assert(Figure::getFigureCount() == beforeHeap);
    
    std::cout << "\n8.3. Массивы объектов:" << std::endl;
    {
        Rectangle rectArray[3] = {
            Rectangle("Array1", 1, 2),
            Rectangle("Array2", 3, 4),
            Rectangle("Array3", 5, 6)
        };
        std::cout << "  Создан массив из 3 Rectangle" << std::endl;
    }
    std::cout << "  Массив уничтожен" << std::endl;
    
    std::cout << "\n8.4. Массивы указателей:" << std::endl;
    Figure* ptrArray[2];
    ptrArray[0] = new Rectangle("Ptr1", 2, 3);
    ptrArray[1] = new Square("Ptr2", 4);
    
    // Удаление каждого элемента
    for (int i = 0; i < 2; i++) {
        delete ptrArray[i];
    }
    std::cout << "  Динамические объекты удалены" << std::endl;
    
    std::cout << "\n✓ Жизненный цикл объектов управляется корректно!" << std::endl;
}

/**
 * @brief Тест граничных случаев и особых сценариев
 */
void testEdgeCases() {
    std::cout << "\n=== Тест 9: Граничные случаи и особые сценарии ===" << std::endl;
    
    std::cout << "9.1. Очень большие и очень маленькие фигуры:" << std::endl;
    {
        Rectangle tiny("Tiny", 0.000001, 0.000001);
        Rectangle huge("Huge", 1000000, 1000000);
        std::cout << "  Tiny area: " << tiny.area() << std::endl;
        std::cout << "  Huge area: " << huge.area() << std::endl;
    }
    
    std::cout << "\n9.2. Квадрат через Rectangle:" << std::endl;
    {
        Rectangle almostSquare("Almost Square", 5.0, 5.0000001);
        Rectangle exactSquare("Exact Square", 5.0, 5.0);
        
        std::cout << "  " << almostSquare.getName() << " isSquare(): " 
                  << (almostSquare.isSquare() ? "true" : "false") << std::endl;
        std::cout << "  " << exactSquare.getName() << " isSquare(): " 
                  << (exactSquare.isSquare() ? "true" : "false") << std::endl;
    }
    
    std::cout << "\n9.3. Изменение имени фигуры:" << std::endl;
    {
        Polygon poly("Old Name");
        poly.setName("New Name");
        std::cout << "  Имя изменено на: " << poly.getName() << std::endl;
        assert(poly.getName() == "New Name");
    }
    
    std::cout << "\n✓ Граничные случаи обрабатываются корректно!" << std::endl;
}

/**
 * @brief Итоговый тест производительности и корректности
 */
void testPerformanceAndCorrectness() {
    std::cout << "\n=== Тест 10: Производительность и итоговая корректность ===" << std::endl;
    
    std::cout << "10.1. Создание множества объектов:" << std::endl;
    const int NUM_OBJECTS = 100;
    Figure** manyFigures = new Figure*[NUM_OBJECTS];
    
    for (int i = 0; i < NUM_OBJECTS; i++) {
        if (i % 3 == 0) {
            manyFigures[i] = new Rectangle("Rect_" + std::to_string(i), i+1, (i+1)*2);
        } else if (i % 3 == 1) {
            manyFigures[i] = new Square("Square_" + std::to_string(i), i+1);
        } else {
            // Создаем простой треугольник
            Point points[3] = {Point(0, 0), Point(i+1, 0), Point((i+1)/2.0, i+1)};
            manyFigures[i] = new Polygon("Poly_" + std::to_string(i), 3, points);
        }
    }
    
    std::cout << "  Создано " << NUM_OBJECTS << " фигур" << std::endl;
    assert(Figure::getFigureCount() >= NUM_OBJECTS);
    
    // Вычисление общей площади
    double totalMassiveArea = 0;
    for (int i = 0; i < NUM_OBJECTS; i++) {
        totalMassiveArea += manyFigures[i]->area();
    }
    std::cout << "  Общая площадь всех фигур: " << totalMassiveArea << std::endl;
    
    // Очистка
    for (int i = 0; i < NUM_OBJECTS; i++) {
        delete manyFigures[i];
    }
    delete[] manyFigures;
    
    std::cout << "\n10.2. Проверка утечек памяти:" << std::endl;
    std::cout << "  После удаления всех объектов осталось фигур: " << Figure::getFigureCount() << std::endl;
    // Мы не можем проверить точное число, т.к. в других тестах могли создаться фигуры
    std::cout << "  (Корректно, если нет активных утечек памяти)" << std::endl;
    
    std::cout << "\n✓ Производительность и корректность на приемлемом уровне!" << std::endl;
}

/**
 * @brief Основная функция тестирования
 */
int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "КОМПЛЕКСНОЕ ТЕСТИРОВАНИЕ ИЕРАРХИИ ГЕОМЕТРИЧЕСКИХ ФИГУР" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // Сохраняем начальное количество фигур
    int initialFigureCount = Figure::getFigureCount();
    std::cout << "Начальное количество фигур: " << initialFigureCount << "\n" << std::endl;
    
    try {
        // Запуск всех тестов
        testAllObjectTypesCreation();
        testPolymorphism();
        testStaticMembers();
        testDeepCopy();
        testVirtualFunctionsWithDefault();
        testMultipleInheritance();
        testExceptionHandling();
        testObjectLifetime();
        testEdgeCases();
        testPerformanceAndCorrectness();
        
        std::cout << "\n==================================================" << std::endl;
        std::cout << "ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!" << std::endl;
        
        // Проверяем, что не осталось утечек
        int finalFigureCount = Figure::getFigureCount();
        std::cout << "Фигур создано за все время: " << (finalFigureCount - initialFigureCount) << std::endl;
        std::cout << "Текущее количество активных фигур: " << finalFigureCount << std::endl;
        
        // Если тесты написны корректно, должно быть 0 или начальное значение
        if (finalFigureCount == initialFigureCount) {
            std::cout << "✓ Утечек памяти не обнаружено!" << std::endl;
        } else {
            std::cout << "Внимание: остались активные фигуры. Проверьте очистку." << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\n!!! ОШИБКА В ТЕСТАХ: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "\n!!! НЕИЗВЕСТНАЯ ОШИБКА В ТЕСТАХ" << std::endl;
        return 1;
    }
    
    std::cout << "==================================================" << std::endl;
    
    return 0;
}