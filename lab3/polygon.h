/**
 * @file polygon.h
 * @brief Класс для представления многоугольников
 * @class Polygon
 * 
 * Хранит координаты вершин многоугольника в динамическом массиве.
 * Реализует методы вычисления площади и рисования для многоугольников.
 */
#ifndef POLYGON_H
#define POLYGON_H

#include "figure.h"

/**
 * @struct Point
 * @brief Структура для хранения координат точки
 */
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Polygon : public Figure {
protected:
    int verticesCount; ///< Количество вершин
    Point* vertices;   ///< Динамический массив координат вершин
    
    /**
     * @brief Вычисляет площадь многоугольника по формуле площади Гаусса
     * @return Площадь многоугольника
     */
    virtual double calculateArea() const;
    
public:
    /**
     * @brief Конструктор многоугольника
     * @param name Название многоугольника
     * @param verticesCount Количество вершин
     * @param vertices Массив вершин (если nullptr, создает пустой)
     */
    Polygon(const std::string& name = "Polygon", 
            int verticesCount = 0, 
            const Point* vertices = nullptr);
    
    /**
     * @brief Конструктор копирования
     * @param other Другой многоугольник
     */
    Polygon(const Polygon& other);
    
    /**
     * @brief Оператор присваивания
     * @param other Другой многоугольник
     * @return Ссылка на текущий объект
     */
    Polygon& operator=(const Polygon& other);
    
    /**
     * @brief Деструктор
     */
    virtual ~Polygon();
    
    /**
     * @brief Реализация виртуальной функции вычисления площади
     * @return Площадь многоугольника
     */
    virtual double area() const override;
    
    /**
     * @brief Реализация функции рисования
     */
    virtual void draw() const override;
    
    /**
     * @brief Получение информации о многоугольнике
     * @return Строка с информацией
     */
    virtual std::string getInfo() const override;
    
    /**
     * @brief Установка вершин многоугольника
     * @param count Количество вершин
     * @param points Массив вершин
     * @throw std::invalid_argument если count < 3
     */
    void setVertices(int count, const Point* points);
    
    /**
     * @brief Получение количества вершин
     * @return Количество вершин
     */
    int getVerticesCount() const { return verticesCount; }
    
    /**
     * @brief Получение вершины по индексу
     * @param index Индекс вершины
     * @return Точка с координатами вершины
     * @throw std::out_of_range если индекс вне диапазона
     */
    Point getVertex(int index) const;
    
    /**
     * @brief Виртуальная функция установки цвета заливки с реализацией по умолчанию
     * @param color Название цвета
     */
    virtual void setFillColor(const std::string& color);
};

#endif // POLYGON_H