/**
 * @file polygon.cpp
 * @brief Реализация методов класса Polygon
 */
#include "polygon.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip>

Polygon::Polygon(const std::string& name, int verticesCount, const Point* vertices) 
    : Figure(name), verticesCount(verticesCount), vertices(nullptr) {
    
    if (verticesCount < 0) {
        throw std::invalid_argument("Vertices count cannot be negative");
    }
    
    // ДОБАВЛЕНО: Проверка минимального количества вершин для многоугольника
    if (verticesCount > 0 && verticesCount < 3) {
        throw std::invalid_argument("Polygon must have at least 3 vertices");
    }
    
    if (verticesCount > 0) {
        this->vertices = new Point[verticesCount];
        if (vertices) {
            for (int i = 0; i < verticesCount; i++) {
                this->vertices[i] = vertices[i];
            }
        } else {
            // Инициализируем нулями
            for (int i = 0; i < verticesCount; i++) {
                this->vertices[i] = Point(0, 0);
            }
        }
    }
}

Polygon::Polygon(const Polygon& other) 
    : Figure(other.name), verticesCount(other.verticesCount), vertices(nullptr) {
    
    if (verticesCount > 0) {
        vertices = new Point[verticesCount];
        for (int i = 0; i < verticesCount; i++) {
            vertices[i] = other.vertices[i];
        }
    }
}

Polygon& Polygon::operator=(const Polygon& other) {
    if (this != &other) {
        // Освобождаем старую память
        delete[] vertices;
        
        // Копируем базовую часть
        name = other.name;
        verticesCount = other.verticesCount;
        
        // Копируем вершины
        if (verticesCount > 0) {
            vertices = new Point[verticesCount];
            for (int i = 0; i < verticesCount; i++) {
                vertices[i] = other.vertices[i];
            }
        } else {
            vertices = nullptr;
        }
    }
    return *this;
}

Polygon::~Polygon() {
    delete[] vertices;
}

double Polygon::calculateArea() const {
    if (verticesCount < 3) return 0.0;
    
    double area = 0.0;
    for (int i = 0; i < verticesCount; i++) {
        int j = (i + 1) % verticesCount;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

double Polygon::area() const {
    return calculateArea();
}

void Polygon::draw() const {
    std::cout << "Drawing " << name << " (polygon with " << verticesCount << " vertices):" << std::endl;
    if (verticesCount == 0) {
        std::cout << "  No vertices defined" << std::endl;
        return;
    }
    
    // Простая ASCII графика
    const int gridSize = 10;
    char grid[gridSize][gridSize];
    
    // Инициализация сетки
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = '.';
        }
    }
    
    // Находим границы координат
    double minX = vertices[0].x, maxX = vertices[0].x;
    double minY = vertices[0].y, maxY = vertices[0].y;
    
    for (int i = 1; i < verticesCount; i++) {
        if (vertices[i].x < minX) minX = vertices[i].x;
        if (vertices[i].x > maxX) maxX = vertices[i].x;
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }
    
    double scaleX = (gridSize - 1) / (maxX - minX + 1);
    double scaleY = (gridSize - 1) / (maxY - minY + 1);
    
    // Рисуем вершины
    for (int i = 0; i < verticesCount; i++) {
        int x = static_cast<int>((vertices[i].x - minX) * scaleX);
        int y = static_cast<int>((vertices[i].y - minY) * scaleY);
        
        if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
            grid[y][x] = 'X';
        }
    }
    
    // Выводим сетку
    for (int i = gridSize - 1; i >= 0; i--) {
        std::cout << "  ";
        for (int j = 0; j < gridSize; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    std::cout << "  Area: " << std::fixed << std::setprecision(2) << area() << std::endl;
}

std::string Polygon::getInfo() const {
    std::stringstream ss;
    ss << Figure::getInfo() << ", Vertices: " << verticesCount 
       << ", Area: " << std::fixed << std::setprecision(2) << area();
    return ss.str();
}

void Polygon::setVertices(int count, const Point* points) {
    if (count < 3) {
        throw std::invalid_argument("Polygon must have at least 3 vertices");
    }
    
    delete[] vertices;
    verticesCount = count;
    
    vertices = new Point[count];
    if (points) {
        for (int i = 0; i < count; i++) {
            vertices[i] = points[i];
        }
    } else {
        for (int i = 0; i < count; i++) {
            vertices[i] = Point(0, 0);
        }
    }
}

Point Polygon::getVertex(int index) const {
    if (index < 0 || index >= verticesCount) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices[index];
}

void Polygon::setFillColor(const std::string& color) {
    std::cout << "Setting fill color of " << name << " to: " << color 
              << " (default Polygon implementation)" << std::endl;
}