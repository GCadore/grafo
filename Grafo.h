#ifndef GRAFO_H
#define GRAFO_H
#include <string>
#include <vector>
#include <queue>

class Grafo {
protected:
    bool direcionado;
    bool ponderado;
    int numArestas;
    int numVertices;

public:
    Grafo(bool dir, bool pond) : direcionado(dir), ponderado(pond), numArestas(0), numVertices(0) {}
    virtual ~Grafo() = default;

    // Funções virtuais puras — implementadas nas subclasses
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

    // Funções concretas da base 
    void bfs(int inicio);
    void buscaProfundidade(int inicio);

    int getNumVertices() const { return numVertices; }
    int getNumArestas() const { return numArestas; }

private:
    // Auxiliar interna da DFS 
    void dfsRecursivo(int v, std::vector<bool>& visitado);
};

#endif