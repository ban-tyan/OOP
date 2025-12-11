/**
 * @file square.cpp
 * @brief Реализация методов класса Square
 */
#include "square.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Square::Square(const std::string& name, double side, double x, double y) 
    : Rectangle(name, side, side, x, y) {
    
    if (side <= 0) {
        throw std::invalid_argument("Side must be positive");
    }
}

Square::Square(const Square& other) 
    : Rectangle(other) {}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        Rectangle::operator=(other);
    }
    return *this;
}

void Square::draw() const {
    std::cout << "Drawing " << name << " (square):" << std::endl;
    
    // ASCII представление квадрата
    const int size = 8;
    
    for (int i = 0; i < size; i++) {
        std::cout << "  ";
        for (int j = 0; j < size; j++) {
            if (i == 0 || i == size - 1 || j == 0 || j == size - 1) {
                std::cout << "#";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "  Side: " << getSide() 
              << ", Area: " << std::fixed << std::setprecision(2) << area() << std::endl;
}

std::string Square::getInfo() const {
    std::stringstream ss;
    ss << Rectangle::getInfo() << ", Side: " << getSide();
    return ss.str();
}

void Square::setFillColor(const std::string& color) {
    std::cout << "Setting fill color of " << name << " to: " << color 
              << " (Square special implementation)" << std::endl;
}

void Square::setSide(double newSide) {
    if (newSide <= 0) {
        throw std::invalid_argument("Side must be positive");
    }
    setDimensions(newSide, newSide);
}