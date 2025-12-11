/**
 * @file drawable.h
 * @brief Интерфейс для рисования объектов
 * @interface Drawable
 * 
 * Интерфейс предоставляет метод рисования объектов.
 * Используется для реализации множественного наследования.
 */
 
#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
public:
    virtual ~Drawable() = default;
    
    /**
     * @brief Чисто виртуальная функция для рисования объекта
     * @pure
     */
    virtual void draw() const = 0;
};

#endif // DRAWABLE_H