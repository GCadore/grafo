#include "ArvoreGeradora.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

// ==========================================
// ALGORITMO DE PRIM
// ==========================================
std::vector<Aresta> ArvoreGeradora::prim(Grafo* grafo) {
    int n = grafo->getNumVertices();
    vector<Aresta> arvore; 
    
    if (n == 0) return arvore;

    vector<bool> emQ(n, true);
    emQ[0] = false;

    for (int i = 0; i < n - 1; i++) {
        
        int u_escolhido = -1;
        int v_escolhido = -1;
        double menorPeso = numeric_limits<double>::max(); 

        for (int u = 0; u < n; u++) {
            if (!emQ[u]) { 
                vector<int> vizinhos = grafo->retornarVizinhos(u);
                
                for (int v : vizinhos) {
                    if (emQ[v]) { 
                        double pesoAresta = grafo->pesoAresta(u, v); 
                        
                        if (pesoAresta < menorPeso) {
                            menorPeso = pesoAresta;
                            u_escolhido = u;
                            v_escolhido = v;
                        }
                    }
                }
            }
        }

        if (u_escolhido != -1 && v_escolhido != -1) {
            arvore.push_back({u_escolhido, v_escolhido, menorPeso});
            emQ[v_escolhido] = false; 
        }
    }

    return arvore;
}

// ==========================================
// ALGORITMO DE KRUSKAL
// ==========================================
std::vector<Aresta> ArvoreGeradora::kruskal(Grafo* grafo) {
    int n = grafo->getNumVertices();
    std::vector<Aresta> arvore;
    
    if (n == 0) return arvore;

    std::vector<Aresta> todasArestas;
    for (int u = 0; u < n; u++) {
        std::vector<int> vizinhos = grafo->retornarVizinhos(u);
        for (int v : vizinhos) {
            if (u < v) {
                float peso = grafo->pesoAresta(u, v);
                todasArestas.push_back({u, v, (double)peso});
            }
        }
    }

    std::sort(todasArestas.begin(), todasArestas.end(), 
        [](const Aresta& a, const Aresta& b) {
            return a.peso < b.peso;
        });

    std::vector<int> pai(n);
    for (int i = 0; i < n; i++) {
        pai[i] = i; 
    }

    std::function<int(int)> find = [&](int i) -> int {
        if (pai[i] == i) return i;
        return pai[i] = find(pai[i]); 
    };

    auto unir = [&](int u, int v) {
        int raizU = find(u);
        int raizV = find(v);
        pai[raizU] = raizV;
    };

    for (const Aresta& aresta : todasArestas) {
        if (find(aresta.origem) != find(aresta.destino)) {
            arvore.push_back(aresta);          
            unir(aresta.origem, aresta.destino); 
            
            if (arvore.size() == n - 1) {
                break;
            }
        }
    }

    return arvore;
}

// ==========================================
// FUNÇÃO DE IMPRIMIR
// ==========================================
void ArvoreGeradora::imprimirResultado(const vector<Aresta>& arvore, double tempoExecucao) {
    cout << "\n===== RESULTADO DA ARVORE GERADORA =====" << endl;
    
    double somaPesos = 0;
    bool imprimirArestas = arvore.size() <= 20;

    if (imprimirArestas) {
        cout << "Arestas selecionadas:\n";
    }

    for (const Aresta& a : arvore) {
        if (imprimirArestas) {
            cout << "  Vertice " << a.origem 
                 << " -- Vertice " << a.destino 
                 << " (Peso: " << a.peso << ")\n";
        }
        somaPesos += a.peso;
    }

    cout << "----------------------------------------\n";
    cout << "Soma total das arestas: " << somaPesos << endl;
    cout << "Tempo de execucao: " << tempoExecucao << " ms" << endl;
    cout << "========================================\n";
}