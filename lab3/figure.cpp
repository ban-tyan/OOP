/**
 * @file figure.cpp
 * @brief Реализация методов класса Figure
 */
#include "figure.h"
#include <stdexcept>
#include <iostream>

// Инициализация статического члена
int Figure::figureCount = 0;

Figure::Figure(const std::string& name) : name(name) {
    figureCount++;
    std::cout << "[DEBUG] Figure created: " << name << " (total: " << figureCount << ")" << std::endl;
}

Figure::~Figure() {
    figureCount--;
    std::cout << "[DEBUG] Figure destroyed: " << name << " (total: " << figureCount << ")" << std::endl;
}

std::string Figure::getInfo() const {
    return "Figure: " + name;
}

int Figure::getFigureCount() {
    return figureCount;
}

double Figure::getAverageArea(double totalArea) {
    if (figureCount == 0) {
        return 0.0;
    }
    return totalArea / figureCount;
}