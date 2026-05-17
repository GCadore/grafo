#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H

#include "Grafo.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>

struct Aresta {
    int destino;
    float peso;
};

class GrafoLista : public Grafo {
private:
    std::vector<std::string> vertices;
    std::vector<std::list<Aresta>> adj;

public:
    GrafoLista(bool dir, bool pond) : Grafo(dir, pond) {}

    bool inserir(std::string label) override;
    bool removerVertice(int indice) override;
    std::string labelVertice(int indice) override;
    void imprimeGrafo() override;
    bool inserirAresta(int origem, int destino, float peso = 1) override;
    bool removerAresta(int origem, int destino) override;
    bool existeAresta(int origem, int destino) override;
    float pesoAresta(int origem, int destino) override;
    std::vector<int> retornarVizinhos(int vertice) override;
    int converterLabel(std::string label) override;
};



#endif