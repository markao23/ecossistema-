#include "Mapa.h"
#include <iostream>

Mapa::Mapa(int l, int a) : largura(l), altura(a) {}

void Mapa::adicionarAnimal(std::shared_ptr<Animal> a) {
    animais.push_back(a);
}

std::shared_ptr<Animal> Mapa::buscarAnimal(int id) {
    for (auto& animal : animais) {
        if (animal->getId() == id) return animal;
    }
    return nullptr; // Retorna nulo se não achar
}

void Mapa::atualizarTurno() {
    for (auto& animal : animais) animal->mover();
}

void Mapa::exibir() const {
    std::cout << "--- Status do Ecossistema ---\n";
    for (const auto& animal : animais) animal->status();
    std::cout << "-----------------------------\n";
}