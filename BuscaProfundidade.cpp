#include "Grafo.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Grafo::buscaProfundidade(int inicio) {
    if (inicio < 0 || inicio >= numVertices) {
        cout << "Indice de vertice invalido!" << endl;
        return;
    }

    vector<bool> visitado(numVertices, false);

    cout << "Resultado da Busca em Profundidade: ";
    dfsRecursivo(inicio, visitado);
    cout << endl;
}

void Grafo::dfsRecursivo(int v, vector<bool>& visitado) {
    visitado[v] = true;
    cout << labelVertice(v) << " ";

    vector<int> vizinhos = retornarVizinhos(v);

    for (int vizinho : vizinhos) {
        if (!visitado[vizinho]) {
            dfsRecursivo(vizinho, visitado);
        }
    }
}