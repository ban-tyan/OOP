#!/usr/bin/env python3
"""
@file plot_points.py
@brief Скрипт для визуализации 3D точек из файла points.txt
@details Использует библиотеки matplotlib и numpy для создания 3D графика
"""

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

def load_points(filename):
    """
    @brief Загрузка точек из файла
    @param filename Имя файла с точками
    @return Три массива координат: x, y, z
    """
    try:
        data = np.loadtxt(filename)
        if data.ndim == 1:  # Если только одна точка
            data = data.reshape(1, -1)
        return data[:,0], data[:,1], data[:,2]
    except Exception as e:
        print(f"Error loading file: {e}")
        return [], [], []

def main():
    """
    @brief Основная функция скрипта визуализации
    """
    try:
        x, y, z = load_points('points.txt')
        
        if len(x) == 0:
            print("No points to visualize.")
            return
        
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        
        # Визуализация точек
        ax.scatter(x, y, z, c='b', marker='o', alpha=0.6)
        
        # Настройка осей
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_title('3D Visualization')
        
        plt.show()
        
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()