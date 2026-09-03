#pragma once
#include <vector>
#include <memory> // Para std::shared_ptr
#include "Animal.h"

class Mapa {
private:
    int largura, altura;
    std::vector<std::shared_ptr<Animal>> animais;

public:
    Mapa(int l, int a);
    void adicionarAnimal(std::shared_ptr<Animal> a);
    std::shared_ptr<Animal> buscarAnimal(int id);
    
    void atualizarTurno();
    void exibir() const;
};