#ifndef ARVOREGERADORA_H
#define ARVOREGERADORA_H

#include "Grafo.h"
#include <vector>

// Estrutura simples para representar o resultado
struct Aresta {
    int origem;
    int destino;
    double peso;
};

class ArvoreGeradora {
public:
    // Retorna a lista de arestas que formam a Árvore Geradora Mínima
    static std::vector<Aresta> prim(Grafo* grafo);
    
    static std::vector<Aresta> kruskal(Grafo* grafo);

    // Utilitário para formatar a saída igual você fez na coloração
    static void imprimirResultado(const std::vector<Aresta>& arvore, double tempoExecucao);
};

#endif