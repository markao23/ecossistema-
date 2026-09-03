#pragma once
#include <string>

class Animal
{
public:
    std::string especie;
    int energia;
    int x, y;
    Animal(std::string esp, int startX, int startY);
    void mover();
    void status() const;
};
