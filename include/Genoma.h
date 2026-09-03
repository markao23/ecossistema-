#pragma once 
#include <string>
#include <unordered_map>     

class Genoma {
    private:
        std::unordered_map<std::string, double> aletos;
    public: 
        Genoma();
        void setGene(const std::string& nome, double valor);
        double getGene(const std::string& nome) const;
        void mutarGene(const std::string& nome, double mutacao);
};