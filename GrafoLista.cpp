#include "GrafoLista.h"

bool GrafoLista::inserir(std::string label) {
    vertices.push_back(label);
    adj.push_back(std::list<Aresta>());
    numVertices++;
    return true;
}

bool GrafoLista::removerVertice(int indice) {
    if (indice < 0 || indice >= (int)vertices.size()) return false;

    vertices.erase(vertices.begin() + indice);
    adj.erase(adj.begin() + indice);

    for (auto& lista : adj) {
        lista.remove_if([indice](const Aresta& a) { return a.destino == indice; });
        for (auto& aresta : lista) {
            if (aresta.destino > indice) aresta.destino--;
        }
    }
    numVertices--;
    return true;
}

bool GrafoLista::inserirAresta(int origem, int destino, float peso) {
    if (origem < 0 || origem >= (int)vertices.size() || destino < 0 || destino >= (int)vertices.size()) return false;

    float p = ponderado ? peso : 1.0f;
    adj[origem].push_back({destino, p});

    if (!direcionado && origem != destino) {
        adj[destino].push_back({origem, p});
    }
    numArestas++;
    return true;
}

bool GrafoLista::removerAresta(int origem, int destino) {
    if (origem < 0 || origem >= (int)vertices.size() || destino < 0 || destino >= (int)vertices.size()) return false;

    adj[origem].remove_if([destino](const Aresta& a) { return a.destino == destino; });

    if (!direcionado) {
        adj[destino].remove_if([origem](const Aresta& a) { return a.destino == origem; });
    }
    numArestas--;
    return true;
}

bool GrafoLista::existeAresta(int origem, int destino) {
    if (origem < 0 || origem >= (int)vertices.size()) return false;
    for (const auto& a : adj[origem]) {
        if (a.destino == destino) return true;
    }
    return false;
}

float GrafoLista::pesoAresta(int origem, int destino) {
    if (origem < 0 || origem >= (int)vertices.size()) return 0;
    for (const auto& a : adj[origem]) {
        if (a.destino == destino) return a.peso;
    }
    return 0;
}

std::vector<int> GrafoLista::retornarVizinhos(int vertice) {
    std::vector<int> vizinhos;
    if (vertice >= 0 && vertice < (int)adj.size()) {
        for (const auto& a : adj[vertice]) {
            vizinhos.push_back(a.destino);
        }
    }
    return vizinhos;
}

void GrafoLista::imprimeGrafo() {
    for (int i = 0; i < (int)vertices.size(); ++i) {
        std::cout << vertices[i] << " (" << i << "): ";
        for (const auto& a : adj[i]) {
            std::cout << "-> " << vertices[a.destino] << "[" << a.peso << "] ";
        }
        std::cout << std::endl;
    }
}

std::string GrafoLista::labelVertice(int indice) {
    return (indice >= 0 && indice < (int)vertices.size()) ? vertices[indice] : "";
}

int GrafoLista::converterLabel(std::string label) {
    for (int i = 0; i < (int)vertices.size(); i++) {
        if (vertices[i] == label) {
            return i;
        }
    }
    return -1;
}