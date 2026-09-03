#include "Mapa.h"
#include <iostream>

Mapa::Mapa(int l, int a) : largura(l), altura(a) {}

void Mapa::addAnimal(const Animal& a) {
    animais.push_back(a);
}

void Mapa::atualizarTurno() {
    for (auto& animal : animais) {
        animal.mover();
    }
}

void Mapa::Exibir() const {
    std::cout << "--- Status do Ecossistema ---\n";
    for (const auto& animal : animais) {
        animal.status();
    }
    std::cout << "-----------------------------\n";
}