/**
 * @file figure.h
 * @brief Абстрактный базовый класс для геометрических фигур
 * @class Figure
 * 
 * Наследует интерфейс Drawable. Содержит чисто виртуальные функции
 * для вычисления площади и рисования фигуры.
 */
#ifndef FIGURE_H
#define FIGURE_H

#include "drawable.h"
#include <string>

class Figure : public Drawable {
protected:
    std::string name; ///< Название фигуры
    static int figureCount; ///< Статический счетчик созданных фигур
    
public:
    /**
     * @brief Конструктор фигуры
     * @param name Название фигуры
     */
    explicit Figure(const std::string& name = "Figure");
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Figure();
    
    /**
     * @brief Получить название фигуры
     * @return Название фигуры
     */
    virtual std::string getName() const { return name; }
    
    /**
     * @brief Чисто виртуальная функция вычисления площади
     * @pure
     * @return Площадь фигуры
     */
    virtual double area() const = 0;
    
    /**
     * @brief Чисто виртуальная функция рисования
     * @pure
     */
    virtual void draw() const override = 0;
    
    /**
     * @brief Виртуальная функция получения информации о фигуре
     * @return Строка с информацией
     */
    virtual std::string getInfo() const;
    
    /**
     * @brief Статическая функция получения количества созданных фигур
     * @return Количество созданных фигур
     */
    static int getFigureCount();
    
    /**
     * @brief Статическая функция получения средней площади всех фигур
     * @param totalArea Общая площадь всех фигур
     * @return Средняя площадь или 0 если фигур нет
     */
    static double getAverageArea(double totalArea);
    
    /**
     * @brief Функция установки имени
     * @param newName Новое имя фигуры
     */
    void setName(const std::string& newName) { name = newName; }
};

#endif // FIGURE_H