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

    // 1. Lê a primeira linha de configuração
    if (!(arquivo >> nVertices >> nArestas >> dir >> pond)) {
        return nullptr;
    }

    // 2. Instancia a implementação escolhida
    Grafo* grafo;
    if (usarMatriz) {
        grafo = new GrafoMatriz(dir, pond);
    } else {
        grafo = new GrafoLista(dir, pond);
    }

    // 3. Insere os vértices (usando labels genéricos "V0", "V1", etc. ou lendo do arquivo)
    for (int i = 0; i < nVertices; ++i) {
        grafo->inserir("V" + std::to_string(i));
    }

    // 4. Lê as arestas restantes do arquivo
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
