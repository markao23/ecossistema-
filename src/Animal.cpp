#include "Animal.h"
#include <iostream>
#include <cstdlib>

Animal::Animal(std::string esp, int startX, int startY)
    : especie(esp), energia(100), x(startX), y(startY) {}

void Animal::mover() {
    x += (rand() % 3) - 1;
    y += (rand() % 3) - 1;
    energia -= 2;
}

void Animal::status() const {
    std::cout << especie << "na pos(" << x << "," << y << ") | Energia: "
        << energia << "\n";
}