/**
 * @file rectangle.h
 * @brief Класс для представления прямоугольника
 * @class Rectangle
 * 
 * Представляет прямоугольник с заданными шириной и высотой.
 * Автоматически вычисляет координаты вершин.
 */
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygon.h"

class Rectangle : public Polygon {
protected:
    double width;  ///< Ширина прямоугольника
    double height; ///< Высота прямоугольника
    
public:
    /**
     * @brief Конструктор прямоугольника
     * @param name Название прямоугольника
     * @param width Ширина
     * @param height Высота
     * @param x Левый нижний угол X
     * @param y Левый нижний угол Y
     * @throw std::invalid_argument если ширина или высота <= 0
     */
    Rectangle(const std::string& name = "Rectangle", 
              double width = 1.0, 
              double height = 1.0,
              double x = 0.0, 
              double y = 0.0);
    
    /**
     * @brief Конструктор копирования
     * @param other Другой прямоугольник
     */
    Rectangle(const Rectangle& other);
    
    /**
     * @brief Оператор присваивания
     * @param other Другой прямоугольник
     * @return Ссылка на текущий объект
     */
    Rectangle& operator=(const Rectangle& other);
    
    /**
     * @brief Переопределенная функция вычисления площади
     * @return Площадь прямоугольника
     */
    virtual double area() const override;
    
    /**
     * @brief Переопределенная функция рисования
     */
    virtual void draw() const override;
    
    /**
     * @brief Переопределенная функция получения информации
     * @return Строка с информацией
     */
    virtual std::string getInfo() const override;
    
    /**
     * @brief Переопределение функции установки цвета заливки
     * @param color Название цвета
     */
    virtual void setFillColor(const std::string& color) override;
    
    /**
     * @brief Получение ширины
     * @return Ширина прямоугольника
     */
    double getWidth() const { return width; }
    
    /**
     * @brief Получение высоты
     * @return Высота прямоугольника
     */
    double getHeight() const { return height; }
    
    /**
     * @brief Установка размеров
     * @param newWidth Новая ширина
     * @param newHeight Новая высота
     * @throw std::invalid_argument если ширина или высота <= 0
     */
    void setDimensions(double newWidth, double newHeight);
    
    /**
     * @brief Проверка, является ли прямоугольник квадратом
     * @return true если квадрат, false если нет
     */
    virtual bool isSquare() const;
};

#endif // RECTANGLE_H