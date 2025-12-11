/**
 * @file square.h
 * @brief Класс для представления квадрата
 * @class Square
 * 
 * Квадрат - частный случай прямоугольника, где ширина равна высоте.
 */
#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"

class Square : public Rectangle {
public:
    /**
     * @brief Конструктор квадрата
     * @param name Название квадрата
     * @param side Длина стороны
     * @param x Левый нижний угол X
     * @param y Левый нижний угол Y
     * @throw std::invalid_argument если сторона <= 0
     */
    Square(const std::string& name = "Square", 
           double side = 1.0,
           double x = 0.0, 
           double y = 0.0);
    
    /**
     * @brief Конструктор копирования
     * @param other Другой квадрат
     */
    Square(const Square& other);
    
    /**
     * @brief Оператор присваивания
     * @param other Другой квадрат
     * @return Ссылка на текущий объект
     */
    Square& operator=(const Square& other);
    
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
     * @brief Получение длины стороны
     * @return Длина стороны квадрата
     */
    double getSide() const { return width; }
    
    /**
     * @brief Установка длины стороны
     * @param newSide Новая длина стороны
     * @throw std::invalid_argument если сторона <= 0
     */
    void setSide(double newSide);
    
    /**
     * @brief Проверка, является ли фигура квадратом (всегда true)
     * @return true (квадрат всегда квадрат)
     */
    virtual bool isSquare() const override { return true; }
};

#endif // SQUARE_H