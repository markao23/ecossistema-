#include "Mapa.h"
#include "Animal.h"
#include <iostream>
#include <ctime>

int main() {
    srand(time(nullptr)); // Initialize random seed

    Mapa ecossistema(10, 10);

    ecossistema.addAnimal(Animal("Lobo", 5, 5));
    ecossistema.addAnimal(Animal("Coelho", 2, 8));

    for (int turno = 0; turno <= 3; turno++)
    {
        std::cout << "Turno: " << turno << "\n";
        ecossistema.atualizarTurno();
        ecossistema.Exibir();
    }
    
    
    return 0;
}