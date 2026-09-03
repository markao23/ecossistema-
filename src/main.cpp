#include "Mapa.h"
#include "Animal.h"
#include <iostream>
#include <ctime>
#include <memory>

int main() {
    srand(time(nullptr));

    Mapa ecossistema(10, 10);

    // Criando animais via Smart Pointers (prática sênior para evitar vazamento de memória)
    auto lobo = std::make_shared<Animal>("Lobo", 5, 5);
    auto coelho = std::make_shared<Animal>("Coelho", 2, 8);

    ecossistema.adicionarAnimal(lobo);
    ecossistema.adicionarAnimal(coelho);

    std::cout << "=> Turno 1 (Base)\n";
    ecossistema.atualizarTurno();
    ecossistema.exibir();

    // INTERVENÇÃO GENÉTICA AVANÇADA (Acessando qualquer animal)
    std::cout << "\n=> Deus intervem! O Coelho recebe o gene 'Pernas Longas'...\n";
    
    // Busca o animal 2 (Coelho) e altera seu gene
    if (auto alvo = ecossistema.buscarAnimal(2)) {
        alvo->dna.setGene("velocidade", 4.0); // O dobro do normal
        alvo->dna.setGene("taxa_metabolica", 3.5); // Gasta mais energia
        alvo->dna.setGene("camuflagem", 10.0); // Criando um gene NOVO do nada
    }

    std::cout << "\n=> Turno 2 (Mutado)\n";
    ecossistema.atualizarTurno();
    ecossistema.exibir();

    return 0;
}