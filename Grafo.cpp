#include "Grafo.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Grafo::bfs(int inicio) {
    if (inicio < 0 || inicio >= numVertices) return;
    vector<bool> visited(numVertices, false);
    queue<int> fila;
    visited[inicio] = true;
    fila.push(inicio);
    cout << "BFS a partir de " << labelVertice(inicio) << ": ";
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        cout << labelVertice(atual) << " ";
        for (int vizinho : retornarVizinhos(atual)) {
            if (!visited[vizinho]) {
                visited[vizinho] = true;
                fila.push(vizinho);
            }
        }
    }
    cout << endl;
}

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