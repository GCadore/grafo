#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

class Grafo {
protected: 
    bool direcionado;
    bool ponderado;

    int numArestas;
    int numVertices;


public:
    Grafo(bool dir, bool pond) : direcionado(dir), ponderado(pond) {}
    virtual ~Grafo() = default;

    
    virtual bool inserir(std::string label) = 0;
    virtual bool removerVertice(int indice) = 0;
    virtual std::string labelVertice(int indice) = 0;
    virtual void imprimeGrafo() = 0;
    virtual bool inserirAresta(int origem, int destino, float peso = 1) = 0;
    virtual bool removerAresta(int origem, int destino) = 0;
    virtual bool existeAresta(int origem, int destino) = 0;
    virtual float pesoAresta(int origem, int destino) = 0;
    virtual std::vector<int> retornarVizinhos(int vertice) = 0;
    virtual int converterLabel(std::string label) = 0;
};

#endif