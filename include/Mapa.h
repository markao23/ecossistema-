#pragma once
#include <vector>
#include "Animal.h"

class Mapa
{
    private:
        int largura, altura;
        std::vector<Animal> animais;
    public:
        Mapa(int l, int c);
        void addAnimal(const Animal& a);
        void atualizarTurno();
        void Exibir() const;
};