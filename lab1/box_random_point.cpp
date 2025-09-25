#include <iostream>
#include <fstream>
#include <algorithm>
#include "box_random_point.h"

using namespace std;

// Конструктор point3d
point3d::point3d(double x, double y, double z) : x(x), y(y), z(z) {}

void point3d::print() const {
    cout << x << " " << y << " " << z << endl;
}

double point3d::getBackX() const { return x; }
double point3d::getBackY() const { return y; }
double point3d::getBackZ() const { return z; }

// Конструктор BoxRandomPoint
BoxRandomPoint::BoxRandomPoint(double mx, double Mx, double my, double My, double mz, double Mz) 
    : pointsArray(nullptr), pointsCount(0), arrayCapacity(0) {
    
    // Обеспечиваем корректность границ
    min_x = min(mx, Mx);
    max_x = max(mx, Mx);
    min_y = min(my, My);
    max_y = max(my, My);
    min_z = min(mz, Mz);
    max_z = max(mz, Mz);
    
    // Инициализация массива с начальной емкостью
    arrayCapacity = 10;
    pointsArray = new point3d[arrayCapacity];
    
    srand(time(0));
    cout << "BoxRandomPoint created with bounds: ";
    printBounds();
}

// Деструктор
BoxRandomPoint::~BoxRandomPoint() {
    delete[] pointsArray;
    cout << "BoxRandomPoint destroyed. Memory freed." << endl;
}

void BoxRandomPoint::setBounds(double mx, double Mx, double my, double My, double mz, double Mz) {
    min_x = min(mx, Mx);
    max_x = max(mx, Mx);
    min_y = min(my, My);
    max_y = max(my, My);
    min_z = min(mz, Mz);
    max_z = max(mz, Mz);
}

point3d BoxRandomPoint::rnd() {
    double x = min_x + (max_x - min_x) * (rand() / (RAND_MAX + 1.0));
    double y = min_y + (max_y - min_y) * (rand() / (RAND_MAX + 1.0));
    double z = min_z + (max_z - min_z) * (rand() / (RAND_MAX + 1.0));
    return point3d(x, y, z);
}

void BoxRandomPoint::generatePoints(int count) {
    for (int i = 0; i < count; ++i) {
        addPoint(rnd());
    }
    cout << "Generated " << count << " points. Total points: " << pointsCount << endl;
}

void BoxRandomPoint::addPoint(const point3d& p) {
    // Проверяем необходимость увеличения массива
    if (pointsCount >= arrayCapacity) {
        resizeArray();
    }
    pointsArray[pointsCount] = p;
    pointsCount++;
}

point3d* BoxRandomPoint::getPoint(int index) const {
    if (index >= 0 && index < pointsCount) {
        return &pointsArray[index];  // Возвращаем указатель на точку
    }
    return nullptr;  // Неверный индекс
}

int BoxRandomPoint::getPointsCount() const {
    return pointsCount;
}

void BoxRandomPoint::printBounds() const {
    cout << "Bounds: x[" << min_x << ", " << max_x << "], y[" 
         << min_y << ", " << max_y << "], z[" << min_z << ", " << max_z << "]" << endl;
}

void BoxRandomPoint::saveSettings(const char* filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << min_x << " " << max_x << endl;
        file << min_y << " " << max_y << endl;
        file << min_z << " " << max_z << endl;
        file.close();
    }
}

void BoxRandomPoint::savePointsToFile(const char* filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < pointsCount; ++i) {
            file << pointsArray[i].x << " " << pointsArray[i].y << " " << pointsArray[i].z << endl;
        }
        file.close();
    }
}

void BoxRandomPoint::printPointsInfo() const {
    cout << "Points in array: " << pointsCount << "/" << arrayCapacity << endl;
    for (int i = 0; i < pointsCount; ++i) {
        cout << "Point " << i << ": ";
        pointsArray[i].print();
    }
}

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