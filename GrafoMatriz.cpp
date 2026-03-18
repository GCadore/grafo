#include "GrafoMatriz.h"
#include <iostream>

GrafoMatriz::GrafoMatriz(bool dir, bool pond) : Grafo(dir, pond) {

}

bool GrafoMatriz::inserir(std::string label){

    for (size_t i = 0; i < matriz.size(); i++) {
    matriz[i].push_back(0.0f);
}

    int novoTamanho = matriz.size() + 1;
    matriz.push_back(std::vector<float>(novoTamanho, 0.0f));

    nomesVertices.push_back(label);
    return true; 
}

bool GrafoMatriz :: removerVertice(int indice){
    matriz.erase(matriz.begin() + indice);
    nomesVertices.erase(nomesVertices.begin() + indice);
    return true;

};

std::string labelVertice(int indice){
    
}