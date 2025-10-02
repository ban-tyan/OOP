#!/usr/bin/env python3
"""
@file plot_points.py  
@brief Максимально простой скрипт визуализации
"""

import numpy as np
import matplotlib
matplotlib.use('TkAgg')  # Явно указываем TkAgg
import matplotlib.pyplot as plt

def main():
    try:
        # Загружаем данные
        data = np.loadtxt('points.txt')
        if data.ndim == 1:
            data = data.reshape(1, -1)
            
        x, y, z = data[:,0], data[:,1], data[:,2]
        print(f"Visualizing {len(x)} points...")
        
        # Простой 3D график
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        
        # Для производительности сэмплируем если точек много
        if len(x) > 5000:
            step = len(x) // 2000
            x, y, z = x[::step], y[::step], z[::step]
            print(f"Sampled to {len(x)} points for performance")
        
        ax.scatter(x, y, z, c=z, s=1, alpha=0.6, cmap='viridis')
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_title('3D Points - Drag to rotate')
        
        print("Plot ready! Drag to rotate, close window to exit.")
        plt.show()
        
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()