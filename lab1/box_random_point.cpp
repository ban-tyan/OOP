#include <iostream>
#include <fstream>
#include <algorithm>
#include "box_random_point.h"

using namespace std;

/**
 * @brief Конструктор структуры point3d
 * @param x Координата X
 * @param y Координата Y
 * @param z Координата Z
 */
point3d::point3d(double x, double y, double z) : x(x), y(y), z(z) {}

/**
 * @brief Вывод координат точки на экран
 */
void point3d::print() const {
    cout << x << " " << y << " " << z << endl;
}

/**
 * @brief Получение координаты X
 * @return Значение координаты X
 */
double point3d::getBackX() const { return x; }

/**
 * @brief Получение координаты Y
 * @return Значение координаты Y
 */
double point3d::getBackY() const { return y; }

/**
 * @brief Получение координаты Z
 * @return Значение координаты Z
 */
double point3d::getBackZ() const { return z; }

/**
 * @brief Конструктор класса BoxRandomPoint
 * @param mx Минимальная координата X
 * @param Mx Максимальная координата X
 * @param my Минимальная координата Y
 * @param My Максимальная координата Y
 * @param mz Минимальная координата Z
 * @param Mz Максимальная координата Z
 * @details Инициализирует границы области и выделяет память для массива точек
 */
BoxRandomPoint::BoxRandomPoint(double mx, double Mx, double my, double My, double mz, double Mz) 
    : pointsArray(nullptr), pointsCount(0), arrayCapacity(0) {
    
    // Обеспечиваем корректность границ (min <= max)
    min_x = min(mx, Mx);
    max_x = max(mx, Mx);
    min_y = min(my, My);
    max_y = max(my, My);
    min_z = min(mz, Mz);
    max_z = max(mz, Mz);
    
    // Инициализация массива с начальной емкостью
    arrayCapacity = 10;
    pointsArray = new point3d[arrayCapacity];
    
    srand(time(0));  // Инициализация генератора случайных чисел
    cout << "BoxRandomPoint created with bounds: ";
    printBounds();
}

/**
 * @brief Деструктор класса BoxRandomPoint
 * @details Освобождает память, выделенную для массива точек
 */
BoxRandomPoint::~BoxRandomPoint() {
    delete[] pointsArray;
    cout << "BoxRandomPoint destroyed. Memory freed." << endl;
}

/**
 * @brief Установка новых границ области
 * @param mx Минимальная координата X
 * @param Mx Максимальная координата X
 * @param my Минимальная координата Y
 * @param My Максимальная координата Y
 * @param mz Минимальная координата Z
 * @param Mz Максимальная координата Z
 */
void BoxRandomPoint::setBounds(double mx, double Mx, double my, double My, double mz, double Mz) {
    // Обеспечиваем корректность границ (min <= max)
    min_x = min(mx, Mx);
    max_x = max(mx, Mx);
    min_y = min(my, My);
    max_y = max(my, My);
    min_z = min(mz, Mz);
    max_z = max(mz, Mz);
}

/**
 * @brief Генерация одной случайной точки в области
 * @return Объект point3d со случайными координатами в заданных границах
 */
point3d BoxRandomPoint::rnd() {
    double x = min_x + (max_x - min_x) * (rand() / (RAND_MAX + 1.0));
    double y = min_y + (max_y - min_y) * (rand() / (RAND_MAX + 1.0));
    double z = min_z + (max_z - min_z) * (rand() / (RAND_MAX + 1.0));
    return point3d(x, y, z);
}

/**
 * @brief Генерация нескольких случайных точек и добавление их в массив
 * @param count Количество точек для генерации
 */
void BoxRandomPoint::generatePoints(int count) {
    for (int i = 0; i < count; ++i) {
        addPoint(rnd());
    }
    cout << "Generated " << count << " points. Total points: " << pointsCount << endl;
}

/**
 * @brief Добавление точки в массив
 * @param p Точка для добавления
 * @note Массив автоматически расширяется при необходимости
 */
void BoxRandomPoint::addPoint(const point3d& p) {
    // Проверяем необходимость увеличения массива
    if (pointsCount >= arrayCapacity) {
        resizeArray();
    }
    pointsArray[pointsCount] = p;
    pointsCount++;
}

/**
 * @brief Получение точки по индексу
 * @param index Индекс точки в массиве
 * @return Указатель на точку или nullptr если индекс неверный
 */
point3d* BoxRandomPoint::getPoint(int index) const {
    if (index >= 0 && index < pointsCount) {
        return &pointsArray[index];  // Возвращаем указатель на точку
    }
    return nullptr;  // Неверный индекс
}

/**
 * @brief Получение количества точек в массиве
 * @return Количество точек
 */
int BoxRandomPoint::getPointsCount() const {
    return pointsCount;
}

/**
 * @brief Вывод текущих границ области на экран
 */
void BoxRandomPoint::printBounds() const {
    cout << "Bounds: x[" << min_x << ", " << max_x << "], y[" 
         << min_y << ", " << max_y << "], z[" << min_z << ", " << max_z << "]" << endl;
}

/**
 * @brief Сохранение параметров области в файл
 * @param filename Имя файла для сохранения
 */
void BoxRandomPoint::saveSettings(const char* filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << min_x << " " << max_x << endl;
        file << min_y << " " << max_y << endl;
        file << min_z << " " << max_z << endl;
        file.close();
    }
}

/**
 * @brief Сохранение всех точек в файл
 * @param filename Имя файла для сохранения
 */
void BoxRandomPoint::savePointsToFile(const char* filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < pointsCount; ++i) {
            file << pointsArray[i].x << " " << pointsArray[i].y << " " << pointsArray[i].z << endl;
        }
        file.close();
    }
}

/**
 * @brief Вывод информации о массиве точек
 * @details Выводит количество точек, емкость массива и координаты всех точек
 */
void BoxRandomPoint::printPointsInfo() const {
    cout << "Points in array: " << pointsCount << "/" << arrayCapacity << endl;
    for (int i = 0; i < pointsCount; ++i) {
        cout << "Point " << i << ": ";
        pointsArray[i].print();
    }
}

/**
 * @brief Увеличение емкости массива при необходимости
 * @details Создает новый массив большего размера и копирует в него старые данные
 */
void BoxRandomPoint::resizeArray() {
    int newCapacity = arrayCapacity * 2;
    point3d* newArray = new point3d[newCapacity];
    
    // Копируем существующие точки
    for (int i = 0; i < pointsCount; ++i) {
        newArray[i] = pointsArray[i];
    }
    
    // Освобождаем старый массив и обновляем указатель
    delete[] pointsArray;
    pointsArray = newArray;
    arrayCapacity = newCapacity;
    
    cout << "Array resized to capacity: " << arrayCapacity << endl;
}