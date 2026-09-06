    #include "Animal.h"
    #include <iostream>
    #include <cstdlib>

    int Animal::geradorId = 0;

    Animal::Animal(std::string esp, int startX, int startY)
        :  id(geradorId++), especie(esp), energia(100.0), x(startX), y(startY) {
            dna.setGene("velocidade", 1.0);
            dna.setGene("taxa_metabolica", 2.0);
        }

    int Animal::getId() const {
        return id;
    }

    void Animal::mover() {
        double vel = dna.getGene("velocidade");
        double taxa = dna.getGene("taxa_metabolica");

        int alcance = static_cast<int>(vel);
        x += (rand() % (alcance * 2 + 1)) - alcance;
        y += (rand() % (alcance * 2 + 1)) - alcance;

        if (x > 10) x = -10;
        else if (x < -10) x = 10;

        if (y > 10) y = -10;
        else if (y < -10) y = 10;

        energia -= taxa;
    }

    void Animal::status() const {
        std::cout << "[ID: " << id <<"] " << especie
            << "na pos(" << x << "," << y << ") | Energia: " << energia << "\n"
            << " | Vel: " << dna.getGene("velocidade") << "\n";
    }