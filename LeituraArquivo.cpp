#include "LeitorArquivo.h"
#include "GrafoMatriz.h"
#include "GrafoLista.h"
#include <fstream>
#include <iostream>

Grafo* LeitorArquivo::carregarGrafo(std::string caminho, bool usarMatriz) {
    std::ifstream arquivo(caminho);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << caminho << std::endl;
        return nullptr;
    }

    int nVertices, nArestas;
    bool dir, pond;

    if (!(arquivo >> nVertices >> nArestas >> dir >> pond)) {
        return nullptr;
    }

    Grafo* grafo;
    if (usarMatriz) {
        grafo = new GrafoMatriz(dir, pond);
    } else {
        grafo = new GrafoLista(dir, pond);
    }

    for (int i = 0; i < nVertices; ++i) {
        grafo->inserir("V" + std::to_string(i));
    }

    int origem, destino;
    float peso;

    for (int i = 0; i < nArestas; ++i) {
        if (pond) {
            arquivo >> origem >> destino >> peso;
            grafo->inserirAresta(origem, destino, peso);
        } else {
            arquivo >> origem >> destino;
            grafo->inserirAresta(origem, destino, 1.0f);
        }
    }

    arquivo.close();
    return grafo;
}
