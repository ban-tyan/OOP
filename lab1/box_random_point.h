#ifndef BOX_RANDOM_POINT_H
#define BOX_RANDOM_POINT_H

#include <cstdlib>
#include <ctime>

/**
 * @struct point3d
 * @brief Структура для хранения трехмерных координат точки
 */
struct point3d {
    double x;  ///< Координата X
    double y;  ///< Координата Y
    double z;  ///< Координата Z

    /**
     * @brief Конструктор инициализации точки
     * @param x Координата X (по умолчанию 0.0)
     * @param y Координата Y (по умолчанию 0.0)
     * @param z Координата Z (по умолчанию 0.0)
     */
    point3d(double x = 0.0, double y = 0.0, double z = 0.0);
    
    /**
     * @brief Вывод координат точки на экран
     */
    void print() const;
    
    /**
     * @brief Получение координаты X
     * @return Значение координаты X
     */
    double getBackX() const;
    
    /**
     * @brief Получение координаты Y
     * @return Значение координаты Y
     */
    double getBackY() const;
    
    /**
     * @brief Получение координаты Z
     * @return Значение координаты Z
     */
    double getBackZ() const;
};

/**
 * @class BoxRandomPoint
 * @brief Класс для генерации случайных точек в параллелепипеде
 * 
 * Класс позволяет генерировать случайные точки в заданной области,
 * ограниченной параллелепипедом. Поддерживает возможность задания
 * плоских областей (когда min == max по некоторой координате)
 * Использует динамическое выделение памяти через указатели
 */
class BoxRandomPoint {
    double min_x;  ///< Минимальная координата X
    double max_x;  ///< Максимальная координата X
    double min_y;  ///< Минимальная координата Y
    double max_y;  ///< Максимальная координата Y
    double min_z;  ///< Минимальная координата Z
    double max_z;  ///< Максимальная координата Z
    
    point3d* pointsArray;  ///< Указатель на массив точек
    int pointsCount;       ///< Количество точек в массиве
    int arrayCapacity;     ///< Вместимость массива

public:
    /**
     * @brief Конструктор инициализации границ области
     * @param mx Минимальная координата X
     * @param Mx Максимальная координата X
     * @param my Минимальная координата Y
     * @param My Максимальная координата Y
     * @param mz Минимальная координата Z
     * @param Mz Максимальная координата Z
     * @warning Если min > max по любой координате, значения будут автоматически поменяны местами
     */
    BoxRandomPoint(double mx, double Mx, double my, double My, double mz, double Mz);
    
    /**
     * @brief Деструктор - освобождает память
     * @details Автоматически вызывается при уничтожении объекта
     */
    ~BoxRandomPoint();
    
    /**
     * @brief Установка новых границ области
     * @param mx Минимальная координата X
     * @param Mx Максимальная координата X
     * @param my Минимальная координата Y
     * @param My Максимальная координата Y
     * @param mz Минимальная координата Z
     * @param Mz Максимальная координата Z
     */
    void setBounds(double mx, double Mx, double my, double My, double mz, double Mz);
    
    /**
     * @brief Генерация одной случайной точки в области
     * @return Объект point3d со случайными координатами в заданных границах
     */
    point3d rnd();
    
    /**
     * @brief Генерация нескольких случайных точек и добавление их в массив
     * @param count Количество точек для генерации
     */
    void generatePoints(int count);
    
    /**
     * @brief Добавление точки в массив
     * @param p Точка для добавления
     * @note Массив автоматически расширяется при необходимости
     */
    void addPoint(const point3d& p);
    
    /**
     * @brief Получение точки по индексу
     * @param index Индекс точки в массиве
     * @return Указатель на точку или nullptr если индекс неверный
     */
    point3d* getPoint(int index) const;
    
    /**
     * @brief Получение количества точек в массиве
     * @return Количество точек
     */
    int getPointsCount() const;
    
    /**
     * @brief Вывод текущих границ области на экран
     */
    void printBounds() const;
    
    /**
     * @brief Сохранение параметров области в файл
     * @param filename Имя файла для сохранения
     */
    void saveSettings(const char* filename) const;
    
    /**
     * @brief Сохранение всех точек в файл
     * @param filename Имя файла для сохранения
     */
    void savePointsToFile(const char* filename) const;
    
    /**
     * @brief Вывод информации о массиве точек
     * @details Выводит количество точек, емкость массива и координаты всех точек
     */
    void printPointsInfo() const;

private:
    /**
     * @brief Увеличение емкости массива при необходимости
     * @details Создает новый массив большего размера и копирует в него старые данные
     */
    void resizeArray();
};

#endif