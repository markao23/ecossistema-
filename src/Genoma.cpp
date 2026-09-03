#include "Genoma.h"

Genoma::Genoma() {}

void Genoma::setGene(const std::string& nome, double valor) {
    aletos[nome] = valor;
}

double Genoma::getGene(const std::string& nome) const {
    auto it = aletos.find(nome);
    if (it != aletos.end())
    {
        return it->second;
    }
    return 1.0;
}

void Genoma::mutarGene(const std::string& nome, double mutacao) {
    aletos[nome] += mutacao;
}