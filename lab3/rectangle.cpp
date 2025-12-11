/**
 * @file rectangle.cpp
 * @brief Реализация методов класса Rectangle
 */
#include "rectangle.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Rectangle::Rectangle(const std::string& name, double width, double height, double x, double y) 
    : Polygon(name, 4), width(width), height(height) {
    
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    
    // Создаем вершины прямоугольника
    Point* verticesArr = new Point[4];
    verticesArr[0] = Point(x, y);
    verticesArr[1] = Point(x + width, y);
    verticesArr[2] = Point(x + width, y + height);
    verticesArr[3] = Point(x, y + height);
    
    setVertices(4, verticesArr);
    delete[] verticesArr;
}

Rectangle::Rectangle(const Rectangle& other) 
    : Polygon(other), width(other.width), height(other.height) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        Polygon::operator=(other);
        width = other.width;
        height = other.height;
    }
    return *this;
}

double Rectangle::area() const {
    return width * height;
}

void Rectangle::draw() const {
    std::cout << "Drawing " << name << " (rectangle):" << std::endl;
    
    // ASCII представление прямоугольника
    const int rows = 8;
    const int cols = 16;
    
    for (int i = 0; i < rows; i++) {
        std::cout << "  ";
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1) {
                std::cout << "-";
            } else if (j == 0 || j == cols - 1) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "  Width: " << width << ", Height: " << height 
              << ", Area: " << std::fixed << std::setprecision(2) << area() << std::endl;
    
    if (isSquare()) {
        std::cout << "  This rectangle is also a square!" << std::endl;
    }
}

std::string Rectangle::getInfo() const {
    std::stringstream ss;
    ss << Polygon::getInfo() << ", Width: " << width << ", Height: " << height;
    if (isSquare()) {
        ss << " (Square)";
    }
    return ss.str();
}

void Rectangle::setFillColor(const std::string& color) {
    std::cout << "Setting fill color of " << name << " to: " << color 
              << " (Rectangle implementation)" << std::endl;
}

void Rectangle::setDimensions(double newWidth, double newHeight) {
    if (newWidth <= 0 || newHeight <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    
    width = newWidth;
    height = newHeight;
    
    // Обновляем вершины
    Point v0 = getVertex(0);
    Point* verticesArr = new Point[4];
    verticesArr[0] = Point(v0.x, v0.y);
    verticesArr[1] = Point(v0.x + width, v0.y);
    verticesArr[2] = Point(v0.x + width, v0.y + height);
    verticesArr[3] = Point(v0.x, v0.y + height);
    
    setVertices(4, verticesArr);
    delete[] verticesArr;
}

bool Rectangle::isSquare() const {
    return std::abs(width - height) < 1e-10;
}