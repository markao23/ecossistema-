#pragma once
#include "Genoma.h"
#include <string>

class Animal
{
    private: 
        static int geradorId;
        int id;
    public:
        std::string especie;
        int energia;
        int x, y;
        Genoma dna;
        Animal(std::string esp, int startX, int startY);
        int getId() const;
        void mover();
        void status() const;
};
