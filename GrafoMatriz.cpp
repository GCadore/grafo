#include "GrafoMatriz.h"
#include <iostream>

GrafoMatriz::GrafoMatriz(bool dir, bool pond) : Grafo(dir, pond) {

}

bool GrafoMatriz::inserir(std::string label){
    // Primeiro expande as linhas existentes com uma nova coluna
    for (auto& linha : matriz) {
        linha.push_back(0.0f);
    }
    // Depois adiciona a nova linha com tamanho correto
    matriz.push_back(std::vector<float>(numVertices + 1, 0.0f));

    nomesVertices.push_back(label);
    numVertices++;
    return true;
}

bool GrafoMatriz::removerVertice(int indice){
    if (indice < 0 || indice >= numVertices) return false;

    // Remove a linha do vértice
    matriz.erase(matriz.begin() + indice);

    // Remove a coluna do vértice em cada linha restante
    for (auto& linha : matriz) {
        linha.erase(linha.begin() + indice);
    }

    nomesVertices.erase(nomesVertices.begin() + indice);
    numVertices--;
    return true;
}

    std::string GrafoMatriz::labelVertice(int indice){
    return nomesVertices[indice];
    
}

void GrafoMatriz::imprimeGrafo(){
    std::cout << numVertices << " " << numArestas << " " << direcionado << " " << ponderado << std::endl;
    for (int i = 0; i < (int)matriz.size(); i++) {
        for (int j = 0; j < (int)matriz[i].size(); j++) {
            if(matriz[i][j] != 0) {
                if (ponderado) {
                    std::cout << i << " " << j << " " << matriz[i][j] << std::endl;
                } else {
                    std::cout << i << " " << j << std::endl;
                }
            }
        }
    }
}

bool GrafoMatriz::inserirAresta(int origem, int destino, float peso){
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        return false;
    }

    matriz[origem][destino] = peso;
    if (!direcionado) {
        matriz[destino][origem] = peso;
    }

    numArestas++;
    return true;

}

bool GrafoMatriz::removerAresta(int origem, int destino){
     if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        return false;
    }
    matriz[origem][destino] = 0;
    if (!direcionado) {
        matriz[destino][origem] = 0;
    }
    numArestas--;
    return true;
}

bool GrafoMatriz::existeAresta(int origem, int destino){
    return matriz[origem][destino] != 0;
}

float GrafoMatriz::pesoAresta(int origem, int destino){
    return matriz[origem][destino];
}

std::vector<int> GrafoMatriz::retornarVizinhos(int vertice){
    std::vector<int> vizinhos;
    for (int i = 0; i < (int)matriz[vertice].size(); i++) {
        if (matriz[vertice][i] != 0) {
            vizinhos.push_back(i);
        }
    }
    return vizinhos;
}

int GrafoMatriz::converterLabel(std::string label){
    for (int i = 0; i < (int)nomesVertices.size(); i++) {
        if (nomesVertices[i] == label) {
            return i;
        }
    }
    return -1;
}