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
 */
BoxRandomPoint::BoxRandomPoint(double mx, double Mx, double my, double My, double mz, double Mz) {
    // Обеспечиваем корректность границ (min <= max)
    min_x = min(mx, Mx);
    max_x = max(mx, Mx);
    min_y = min(my, My);
    max_y = max(my, My);
    min_z = min(mz, Mz);
    max_z = max(mz, Mz);
    
    srand(time(0));  // Инициализация генератора случайных чисел
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
 * @brief Генерация случайной точки в области
 * @return Объект point3d со случайными координатами в заданных границах
 */
point3d BoxRandomPoint::rnd() {
    double x = min_x + (max_x - min_x) * (rand() / (RAND_MAX + 1.0));
    double y = min_y + (max_y - min_y) * (rand() / (RAND_MAX + 1.0));
    double z = min_z + (max_z - min_z) * (rand() / (RAND_MAX + 1.0));
    return point3d(x, y, z);
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
void BoxRandomPoint::saveSet(const char* filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << min_x << " " << max_x << endl;
        file << min_y << " " << max_y << endl;
        file << min_z << " " << max_z << endl;
        file.close();
    }
}