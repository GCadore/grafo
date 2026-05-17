#include "Grafo.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>


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

void Grafo::dijkstra(int verticeInicial) {

    if (verticeInicial < 0 || verticeInicial >= numVertices) {
        std::cout << "Indice de vertice invalido para o Dijkstra!" << std::endl;
        return;
    }

    //declaração do valor de infinito
    float infinito = std::numeric_limits<float>::infinity();

    std::vector<EstadoVertice> tabela(numVertices);

    for (int i = 0; i < numVertices; i++) {
        tabela[i].distancia = infinito;
        tabela[i].anterior = -1;
        tabela[i].fechado = false;
    }

    tabela[verticeInicial].distancia = 0.0f;


    std::cout << "Iniciando Dijkstra a partir do vertice " << labelVertice(verticeInicial) << "..." << std::endl;

    bool todosFechados = false;

    while(!todosFechados){

        int verticeAtual;
        float menorDistancia = infinito;
        
        //varre a tabela em busca da menor distancia para definir vértice atual (no primeiro while sempre é o vertice inicial)
        for(int i=0; i<numVertices; i++){
            
            if(tabela[i].distancia <= menorDistancia && !tabela[i].fechado){
                menorDistancia = tabela[i].distancia;
                verticeAtual = i;
            }
        }

        //condição de parada caso hajam vértices inalcançáveis
        if (menorDistancia == infinito) break;

        std::vector<int> vizinhos = retornarVizinhos(verticeAtual);

        for(int i=0; i<vizinhos.size(); i++){

            int idVizinho = vizinhos[i];
            float distanciaNova = tabela[verticeAtual].distancia + pesoAresta(verticeAtual, idVizinho);

            if(!tabela[idVizinho].fechado && tabela[idVizinho].distancia > distanciaNova){
                tabela[idVizinho].distancia = distanciaNova;
                tabela[idVizinho].anterior = verticeAtual;
            }
        }

        tabela[verticeAtual].fechado = true;

        todosFechados = true;

        for(int i=0; i<numVertices; i++){
            if(!tabela[i].fechado) todosFechados = false;
        }
    }

    string textoVertice = labelVertice(verticeInicial);
    cout << "imprimindo Djikstra para vertice " << textoVertice << endl;

    for (int i = 0; i < numVertices; i++) {

        cout << "Para " << labelVertice(i) << " -> Distancia minima: ";
        
        if (tabela[i].distancia == infinito) {
            cout << "Inalcancavel\n";
        } else {
            cout << tabela[i].distancia << " | Caminho: ";
            
            // 1. Rastrear o caminho de trás para frente
            vector<int> caminho;
            int atual = i;
            while (atual != -1) {
                caminho.push_back(atual);
                atual = tabela[atual].anterior;
            }
            
            // 2. Imprimir na ordem correta (da origem até o destino)
            for (int j = caminho.size() - 1; j >= 0; j--) {
                cout << labelVertice(caminho[j]);
                if (j > 0) cout << " -> "; // Coloca a setinha entre os vértices
            }
            cout << endl;
        }
    }
}