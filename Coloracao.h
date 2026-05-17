#ifndef COLORACAO_H
#define COLORACAO_H

#include "Grafo.h"
#include <vector>

class Coloracao {
public:

    // Algoritmos
    static std::vector<int> guloso(Grafo* grafo);

    static std::vector<int> welshPowell(Grafo* grafo);

    static std::vector<int> dsatur(Grafo* grafo);

    static std::vector<int> forcaBruta(Grafo* grafo);

    // Utilitários
    static bool corValida(Grafo* grafo,int vertice,int cor,const std::vector<int>& cores);

    static int quantidadeCores(const std::vector<int>& cores);

    static int calcularSaturacao(Grafo* grafo,int vertice,const std::vector<int>& cores);

    static void imprimirResultado(Grafo* grafo,const std::vector<int>& cores,double tempoExecucao);

private:

   static bool backtracking(Grafo* grafo,int verticeAtual,int maxCores,std::vector<int>& cores);
};

#endif