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
 * - Генерация случайных точек
 * - Взаимодействие с пользователем через меню
 */
int main() {
    double mx, Mx, my, My, mz, Mz;
    cout << "Enter bounds for x (min max): ";
    cin >> mx >> Mx;
    cout << "Enter bounds for y (min max): ";
    cin >> my >> My;
    cout << "Enter bounds for z (min max): ";
    cin >> mz >> Mz;

    // Создание генератора точек
    BoxRandomPoint generator(mx, Mx, my, My, mz, Mz);
    
    // Сохранение параметров области
    generator.saveSet("settings.dat");
    cout << "Settings saved to settings.dat" << endl;

    int K;
    cout << "Enter number of points: ";
    cin >> K;

    // Генерация точек
    vector<point3d> points;
    for (int i = 0; i < K; ++i) {
        points.push_back(generator.rnd());
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print point\n";
        cout << "2. Print coordinate\n";
        cout << "3. Add point\n";
        cout << "4. Save to file\n";
        cout << "5. Print bounds\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            int index;
            cout << "Enter index: ";
            cin >> index;
            if (index >= 0 && index < points.size()) {
                points[index].print();
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 2) {
            int index;
            char coord;
            cout << "Enter index and coordinate (x, y, z): ";
            cin >> index >> coord;
            if (index >= 0 && index < points.size()) {
                switch(coord) {
                    case 'x': cout << points[index].getBackX() << endl; break;
                    case 'y': cout << points[index].getBackY() << endl; break;
                    case 'z': cout << points[index].getBackZ() << endl; break;
                    default: cout << "Invalid coordinate!" << endl;
                }
            } else {
                cout << "Invalid index!" << endl;
            }
        } else if (choice == 3) {
            double x, y, z;
            cout << "Enter x y z: ";
            cin >> x >> y >> z;
            points.emplace_back(x, y, z);
            cout << "Point added. Total points: " << points.size() << endl;
        } else if (choice == 4) {
            ofstream file("points.txt");
            for (const auto& p : points) {
                file << p.x << " " << p.y << " " << p.z << endl;
            }
            file.close();
            cout << "Saved " << points.size() << " points to points.txt" << endl;
        } else if (choice == 5) {
            generator.printBounds();
        } else if (choice != 6) {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 6);

    return 0;
}