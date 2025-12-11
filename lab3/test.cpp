/**
 * @file test.cpp
 * @brief Дополнительные комплексные тесты для демонстрации требований
 */
#include <iostream>
#include <cassert>
#include <cmath>
#include <typeinfo>
#include "figure.h"
#include "polygon.h"
#include "rectangle.h"
#include "square.h"

// Вспомогательная функция для тестирования полиморфизма
void testPolymorphicBehavior(Figure* figure, const std::string& expectedType) {
    std::cout << "  Тестируем " << figure->getName() << ":" << std::endl;
    
    // Проверяем тип через typeid
    std::cout << "    Фактический тип: " << typeid(*figure).name() << std::endl;
    
    // Полиморфный вызов area()
    double area = figure->area();
    std::cout << "    Площадь (полиморфно): " << area << std::endl;
    
    // Полиморфный вызов draw()
    std::cout << "    draw() вывод: ";
    figure->draw();
    
    // Проверка через dynamic_cast
    if (expectedType == "Square") {
        Square* square = dynamic_cast<Square*>(figure);
        assert(square != nullptr);
        assert(square->isSquare());
        std::cout << "    ✓ Успешно преобразован к Square" << std::endl;
    } else if (expectedType == "Rectangle") {
        Rectangle* rect = dynamic_cast<Rectangle*>(figure);
        assert(rect != nullptr);
        std::cout << "    ✓ Успешно преобразован к Rectangle" << std::endl;
    } else if (expectedType == "Polygon") {
        Polygon* poly = dynamic_cast<Polygon*>(figure);
        assert(poly != nullptr);
        std::cout << "    ✓ Успешно преобразован к Polygon" << std::endl;
    }
}

int main() {
    std::cout << "КОМПЛЕКСНЫЕ ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ" << std::endl;
    std::cout << "================================" << std::endl;
    
    // ========== Тест 1: Демонстрация невозможности создания абстрактных классов ==========
    std::cout << "\n1. Демонстрация абстрактности класса Figure:" << std::endl;
    std::cout << "   Следующий код вызовет ошибку компиляции:" << std::endl;
    std::cout << "   -----------------------------------------" << std::endl;
    std::cout << "   // Figure abstractFigure(\"Abstract\");" << std::endl;
    std::cout << "   // Ошибка: cannot declare variable 'abstractFigure'" << std::endl;
    std::cout << "   //          to be of abstract type 'Figure'" << std::endl;
    std::cout << "   -----------------------------------------" << std::endl;
    std::cout << "   Это корректно, так как Figure содержит чисто виртуальные функции.\n" << std::endl;
    
    // ========== Тест 2: Проверка глубокого копирования с вложенными данными ==========
    std::cout << "2. Углубленный тест глубокого копирования:" << std::endl;
    {
        // Создаем сложный многоугольник
        Point complexPoints[5];
        for (int i = 0; i < 5; i++) {
            complexPoints[i] = Point(i * 2, i * i);
        }
        
        Polygon original("Complex Polygon", 5, complexPoints);
        
        // Копируем тремя разными способами
        Polygon copy1 = original;                     // Конструктор копирования
        Polygon copy2(original);                      // Явный конструктор копирования
        Polygon copy3 = Polygon("Temp", 0, nullptr);  // Конструктор + присваивание
        copy3 = original;
        
        // Модифицируем оригинал
        original.setName("Modified Original");
        Point newPoints[3] = {Point(0,0), Point(10,0), Point(5,8.66)};
        original.setVertices(3, newPoints);
        
        // Проверяем, что копии не изменились
        assert(copy1.getVerticesCount() == 5);
        assert(copy2.getVerticesCount() == 5);
        assert(copy3.getVerticesCount() == 5);
        assert(original.getVerticesCount() == 3);
        
        std::cout << "   ✓ Глубокое копирование работает даже для сложных структур данных\n" << std::endl;
    }
    
    // ========== Тест 3: Проверка статических членов в многопоточном сценарии (имитация) ==========
    std::cout << "3. Статические члены в различных сценариях:" << std::endl;
    {
        int startCount = Figure::getFigureCount();
        
        // Создаем фигуры в разных областях видимости
        {
            Rectangle r1("R1", 1, 2);
            Square s1("S1", 3);
            assert(Figure::getFigureCount() == startCount + 2);
        }
        
        // После выхода из области видимости счетчик должен уменьшиться
        assert(Figure::getFigureCount() == startCount);
        
        // Динамическое создание и удаление
        Figure* figures[5];
        for (int i = 0; i < 5; i++) {
            if (i % 2 == 0) {
                figures[i] = new Rectangle("Dynamic", i+1, i+2);
            } else {
                figures[i] = new Square("Dynamic", i+1);
            }
        }
        assert(Figure::getFigureCount() == startCount + 5);
        
        // Удаляем в случайном порядке
        delete figures[2];
        delete figures[0];
        delete figures[4];
        delete figures[1];
        delete figures[3];
        
        assert(Figure::getFigureCount() == startCount);
        std::cout << "   ✓ Статические члены корректно работают при сложных сценариях создания/удаления\n" << std::endl;
    }
    
    // ========== Тест 4: Полная проверка полиморфизма ==========
    std::cout << "4. Полная проверка полиморфизма:" << std::endl;
    {
        // Создаем массив указателей на базовый класс
        Figure* polymorphicArray[4];
        
        // Заполняем разными типами
        polymorphicArray[0] = new Rectangle("Polymorphic Rect", 4, 5);
        polymorphicArray[1] = new Square("Polymorphic Square", 6);
        
        // Создаем пятиугольник
        Point pentagon[5];
        for (int i = 0; i < 5; i++) {
            double angle = 2 * M_PI * i / 5;
            pentagon[i] = Point(std::cos(angle) * 4, std::sin(angle) * 4);
        }
        polymorphicArray[2] = new Polygon("Polymorphic Pentagon", 5, pentagon);
        
        // Еще один прямоугольник, который является квадратом
        polymorphicArray[3] = new Rectangle("Square-like Rect", 7, 7);
        
        // Тестируем каждый элемент массива полиморфно
        for (int i = 0; i < 4; i++) {
            std::cout << "   Элемент " << i << ": ";
            
            // Все эти вызовы являются полиморфными
            std::cout << "Имя: " << polymorphicArray[i]->getName();
            std::cout << ", Площадь: " << polymorphicArray[i]->area();
            std::cout << ", Тип: " << typeid(*polymorphicArray[i]).name();
            
            // Проверяем возможность downcast
            if (Square* s = dynamic_cast<Square*>(polymorphicArray[i])) {
                std::cout << " (можно использовать как Square)";
            } else if (Rectangle* r = dynamic_cast<Rectangle*>(polymorphicArray[i])) {
                std::cout << " (можно использовать как Rectangle)";
                if (r->isSquare()) {
                    std::cout << " [является квадратом]";
                }
            }
            std::cout << std::endl;
        }
        
        // Очистка
        for (int i = 0; i < 4; i++) {
            delete polymorphicArray[i];
        }
        std::cout << "   ✓ Полиморфизм работает полностью корректно\n" << std::endl;
    }
    
    // ========== Тест 5: Проверка множественного наследования ==========
    std::cout << "5. Детальная проверка множественного наследования:" << std::endl;
    {
        Square square("MI Test", 8.0);
        
        // Проверяем все возможные преобразования
        Drawable* asDrawable = &square;    // Square* → Drawable*
        Figure* asFigure = &square;        // Square* → Figure*
        Polygon* asPolygon = &square;      // Square* → Polygon*
        Rectangle* asRectangle = &square;  // Square* → Rectangle*
        Square* asSquare = &square;        // Square* → Square*
        
        // Проверяем, что все указатели ненулевые
        assert(asDrawable != nullptr);
        assert(asFigure != nullptr);
        assert(asPolygon != nullptr);
        assert(asRectangle != nullptr);
        assert(asSquare != nullptr);
        
        // Проверяем обратные преобразования
        Square* backFromDrawable = dynamic_cast<Square*>(asDrawable);
        Square* backFromFigure = dynamic_cast<Square*>(asFigure);
        Square* backFromPolygon = dynamic_cast<Square*>(asPolygon);
        Square* backFromRectangle = dynamic_cast<Square*>(asRectangle);
        
        assert(backFromDrawable != nullptr);
        assert(backFromFigure != nullptr);
        assert(backFromPolygon != nullptr);
        assert(backFromRectangle != nullptr);
        
        std::cout << "   Square может быть преобразован ко всем базовым типам и обратно\n" << std::endl;
        
        // Проверяем виртуальные вызовы через разные интерфейсы
        std::cout << "   Виртуальные вызовы через разные интерфейсы:" << std::endl;
        std::cout << "     Через Drawable*: ";
        asDrawable->draw();
        
        std::cout << "     Через Figure*: ";
        asFigure->draw();
        
        std::cout << "     Через Polygon*: ";
        asPolygon->draw();
        
        std::cout << "     Через Rectangle*: ";
        asRectangle->draw();
        
        std::cout << "   ✓ Все виртуальные вызовы работают корректно\n" << std::endl;
    }
    
    // ========== Тест 6: Проверка обработки исключений в граничных случаях ==========
    std::cout << "6. Расширенная проверка обработки исключений:" << std::endl;
    {
        std::cout << "   Тест 6.1: Некорректные параметры конструкторов:" << std::endl;
        
        // Массив тестовых случаев: {тип, параметр1, параметр2, должно_быть_исключение}
        struct TestCase {
            std::string type;
            double param1;
            double param2;
            bool shouldThrow;
        };
        
        // Не все эти тесты можно выполнить без создания новых классов,
        // но демонстрируем принцип
        try {
            Rectangle("Test", 0, 5);  // Нулевая ширина
            std::cout << "     ОШИБКА: Должно быть исключение для ширины 0" << std::endl;
            assert(false);
        } catch (const std::invalid_argument&) {
            std::cout << "     ✓ Корректное исключение для ширины 0" << std::endl;
        }
        
        try {
            Rectangle("Test", 5, -1);  // Отрицательная высота
            std::cout << "     ОШИБКА: Должно быть исключение для высоты -1" << std::endl;
            assert(false);
        } catch (const std::invalid_argument&) {
            std::cout << "     ✓ Корректное исключение для высоты -1" << std::endl;
        }
        
        try {
            Square("Test", -0.001);  // Отрицательная сторона
            std::cout << "     ОШИБКА: Должно быть исключение для стороны -0.001" << std::endl;
            assert(false);
        } catch (const std::invalid_argument&) {
            std::cout << "     ✓ Корректное исключение для стороны -0.001" << std::endl;
        }
        
        std::cout << "\n   Тест 6.2: Исключения при работе с методами:" << std::endl;
        
        try {
            Polygon emptyPoly("Empty");
            emptyPoly.getVertex(0);  // Пустой полигон
            std::cout << "     ОШИБКА: Должно быть исключение для пустого полигона" << std::endl;
            assert(false);
        } catch (const std::out_of_range&) {
            std::cout << "     ✓ Корректное исключение для пустого полигона" << std::endl;
        }
        
        Rectangle rect("Test", 5, 5);
        try {
            rect.setDimensions(0, 10);  // Нулевая ширина
            std::cout << "     ОШИБКА: Должно быть исключение для setDimensions(0, 10)" << std::endl;
            assert(false);
        } catch (const std::invalid_argument&) {
            std::cout << "     ✓ Корректное исключение для setDimensions(0, 10)" << std::endl;
        }
        
        std::cout << "   ✓ Все исключения обрабатываются корректно\n" << std::endl;
    }
    
    // ========== Тест 7: Проверка корректности вычислений ==========
    std::cout << "7. Проверка корректности вычислений:" << std::endl;
    {
        // Прямоугольник 3x4 должен иметь площадь 12
        Rectangle rect3x4("3x4", 3, 4);
        assert(std::abs(rect3x4.area() - 12.0) < 0.0001);
        std::cout << "   ✓ Rectangle 3x4: площадь = " << rect3x4.area() << " (ожидалось 12)" << std::endl;
        
        // Квадрат со стороной 5 должен иметь площадь 25
        Square square5("5x5", 5);
        assert(std::abs(square5.area() - 25.0) < 0.0001);
        std::cout << "   ✓ Square 5x5: площадь = " << square5.area() << " (ожидалось 25)" << std::endl;
        
        // Треугольник (0,0), (4,0), (0,3) должен иметь площадь 6
        Point trianglePoints[3] = {Point(0, 0), Point(4, 0), Point(0, 3)};
        Polygon triangle("Triangle", 3, trianglePoints);
        double triangleArea = triangle.area();
        assert(std::abs(triangleArea - 6.0) < 0.0001);
        std::cout << "   ✓ Triangle (0,0)-(4,0)-(0,3): площадь = " << triangleArea << " (ожидалось 6)" << std::endl;
        
        // Проверка isSquare()
        Rectangle squareLike("SquareLike", 5, 5);
        Rectangle notSquare("NotSquare", 5, 5.0001);
        assert(squareLike.isSquare());
        assert(!notSquare.isSquare());
        std::cout << "   ✓ isSquare() корректно определяет квадраты" << std::endl;
        
        std::cout << "   ✓ Все вычисления выполняются корректно\n" << std::endl;
    }
    
    std::cout << "========================================" << std::endl;
    std::cout << "ВСЕ ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}