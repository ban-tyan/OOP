#include <iostream>
#include <fstream>
#include <vector>
#include "box_random_point.h"

using namespace std;

/**
 * @brief Главная функция программы
 * @return Код завершения программы (0 - успешное выполнение)
 * 
 * Программа демонстрирует работу с классом BoxRandomPoint:
 * - Задание параметров области
 * - Генерация случайных точек с использованием указателей
 * - Динамическое управление памятью
 * - Взаимодействие с пользователем через меню
 * 
 * @note Программа использует динамическое выделение памяти и указатели
 * для работы с массивом точек, что позволяет эффективно управлять памятью
 */
int main() {
    double mx, Mx, my, My, mz, Mz;
    cout << "Enter bounds for x (min max): ";
    cin >> mx >> Mx;
    cout << "Enter bounds for y (min max): ";
    cin >> my >> My;
    cout << "Enter bounds for z (min max): ";
    cin >> mz >> Mz;

    // Создание генератора точек (используется конструктор)
    BoxRandomPoint generator(mx, Mx, my, My, mz, Mz);
    
    // Генерация начального набора точек
    int K;
    cout << "Enter number of points to generate: ";
    cin >> K;
    generator.generatePoints(K);
    
    // Сохранение параметров области
    generator.saveSettings("settings.dat");
    cout << "Settings saved to settings.dat" << endl;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print point\n";
        cout << "2. Print coordinate\n";
        cout << "3. Add point\n";
        cout << "4. Save to file\n";
        cout << "5. Print bounds\n";
        cout << "6. Print points info\n";
        cout << "7. Generate more points\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int index;
            cout << "Enter index: ";
            cin >> index;
            point3d* pointPtr = generator.getPoint(index);
            if (pointPtr != nullptr) {
                pointPtr->print();
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 2) {
            int index;
            char coord;
            cout << "Enter index and coordinate (x, y, z): ";
            cin >> index >> coord;
            point3d* pointPtr = generator.getPoint(index);
            if (pointPtr != nullptr) {
                switch(coord) {
                    case 'x': cout << pointPtr->getBackX() << endl; break;
                    case 'y': cout << pointPtr->getBackY() << endl; break;
                    case 'z': cout << pointPtr->getBackZ() << endl; break;
                    default: cout << "Invalid coordinate!" << endl;
                }
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 3) {
            double x, y, z;
            cout << "Enter x y z: ";
            cin >> x >> y >> z;
            generator.addPoint(point3d(x, y, z));
            cout << "Point added. Total points: " << generator.getPointsCount() << endl;
        } else if (choice == 4) {
            generator.savePointsToFile("points.txt");
            cout << "Saved " << generator.getPointsCount() << " points to points.txt" << endl;
        } else if (choice == 5) {
            generator.printBounds();
        } else if (choice == 6) {
            generator.printPointsInfo();
        } else if (choice == 7) {
            int additionalPoints;
            cout << "Enter number of additional points to generate: ";
            cin >> additionalPoints;
            generator.generatePoints(additionalPoints);
        } else if (choice != 8) {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);

    // Деструктор автоматически вызовется при выходе из области видимости
    return 0;
}