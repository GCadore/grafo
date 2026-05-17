#include "Coloracao.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <set>

using namespace std;

int Coloracao::quantidadeCores(const vector<int>& cores) {

    int maior = -1;

    for (int cor : cores) {
        if (cor > maior) {
            maior = cor;
        }
    }

    return maior + 1;
}

bool Coloracao::corValida(
    Grafo* grafo,
    int vertice,
    int cor,
    const vector<int>& cores
) {

    vector<int> vizinhos = grafo->retornarVizinhos(vertice);

    for (int vizinho : vizinhos) {

        if (cores[vizinho] == cor) {
            return false;
        }
    }

    return true;
}

void Coloracao::imprimirResultado(
    Grafo* grafo,
    const vector<int>& cores,
    double tempoExecucao
) {

    cout << "\n===== RESULTADO DA COLORACAO =====" << endl;

    cout << "Quantidade de cores utilizadas: "
         << quantidadeCores(cores)
         << endl;

    cout << "Tempo de execucao: "
         << tempoExecucao
         << " ms"
         << endl;

    if (grafo->getNumVertices() < 10) {

        cout << "\nVertices e suas cores:\n";

        for (int i = 0; i < (int)cores.size(); i++) {

            cout << "Vertice "
                 << i
                 << " -> Cor "
                 << cores[i]
                 << endl;
        }
    }

    cout << "==================================\n";
}

std::vector<int> Coloracao::guloso(Grafo* grafo) {

    int n = grafo->getNumVertices();

    // Todas as cores começam como "não atribuídas"
    vector<int> cores(n, -1);

    // Percorre todos os vértices em ordem natural
    for (int vertice = 0; vertice < n; vertice++) {

        int corAtual = 0;

        // Procura a menor cor válida
        while (true) {

            if (corValida(grafo, vertice, corAtual, cores)) {

                cores[vertice] = corAtual;
                break;
            }

            corAtual++;
        }
    }

    return cores;
}

std::vector<int> Coloracao::welshPowell(Grafo* grafo) {

    int n = grafo->getNumVertices();

    vector<int> cores(n, -1);

    vector<int> vertices;

    // Cria vetor de vértices
    for (int i = 0; i < n; i++) {
        vertices.push_back(i);
    }

    // Ordena por grau decrescente
    sort(vertices.begin(), vertices.end(),
        [grafo](int a, int b) {

            return grafo->retornarVizinhos(a).size() >
                   grafo->retornarVizinhos(b).size();
        }
    );

    int corAtual = 0;

    // Enquanto existir vértice sem cor
    while (true) {

        bool pintouAlgum = false;

        for (int vertice : vertices) {

            // Ignora já coloridos
            if (cores[vertice] != -1) {
                continue;
            }

            // Tenta pintar com a cor atual
            if (corValida(grafo, vertice, corAtual, cores)) {

                cores[vertice] = corAtual;
                pintouAlgum = true;
            }
        }

        // Verifica se ainda existem vértices sem cor
        bool terminou = true;

        for (int cor : cores) {

            if (cor == -1) {
                terminou = false;
                break;
            }
        }

        if (terminou) {
            break;
        }

        // Próxima cor
        corAtual++;

        // Segurança
        if (!pintouAlgum) {
            break;
        }
    }

    return cores;
}

int Coloracao::calcularSaturacao(
    Grafo* grafo,
    int vertice,
    const vector<int>& cores
) {

    set<int> coresAdjacentes;

    vector<int> vizinhos =
        grafo->retornarVizinhos(vertice);

    for (int vizinho : vizinhos) {

        if (cores[vizinho] != -1) {

            coresAdjacentes.insert(
                cores[vizinho]
            );
        }
    }

    return coresAdjacentes.size();
}

std::vector<int> Coloracao::dsatur(Grafo* grafo) {

    int n = grafo->getNumVertices();

    vector<int> cores(n, -1);

    // Calcula graus
    vector<int> graus(n);

    for (int i = 0; i < n; i++) {

        graus[i] =
            grafo->retornarVizinhos(i).size();
    }

    // Escolhe vértice de maior grau inicialmente
    int primeiro = 0;

    for (int i = 1; i < n; i++) {

        if (graus[i] > graus[primeiro]) {
            primeiro = i;
        }
    }

    // Primeira cor
    cores[primeiro] = 0;

    // Enquanto houver vértices sem cor
    while (true) {

        int escolhido = -1;

        int maiorSaturacao = -1;

        // Escolhe vértice com maior saturação
        for (int i = 0; i < n; i++) {

            if (cores[i] != -1) {
                continue;
            }

            int saturacao =
                calcularSaturacao(
                    grafo,
                    i,
                    cores
                );

            if (saturacao > maiorSaturacao) {

                maiorSaturacao = saturacao;
                escolhido = i;
            }

            // Empate -> maior grau
            else if (
                saturacao == maiorSaturacao &&
                escolhido != -1 &&
                graus[i] > graus[escolhido]
            ) {

                escolhido = i;
            }
        }

        // Terminou
        if (escolhido == -1) {
            break;
        }

        // Escolhe menor cor válida
        int corAtual = 0;

        while (true) {

            if (
                corValida(
                    grafo,
                    escolhido,
                    corAtual,
                    cores
                )
            ) {

                cores[escolhido] = corAtual;
                break;
            }

            corAtual++;
        }
    }

    return cores;
}

bool Coloracao::backtracking(
    Grafo* grafo,
    int verticeAtual,
    int maxCores,
    vector<int>& cores
) {

    int n = grafo->getNumVertices();

    // Todos coloridos
    if (verticeAtual == n) {

        cout << "\nSOLUCAO ENCONTRADA!\n";

        return true;
    }

    cout << "\n[VERTICE " << verticeAtual << "]\n";

    // Testa todas as cores
    for (int cor = 0; cor < maxCores; cor++) {

        cout << "Tentando cor "
             << cor
             << " no vertice "
             << verticeAtual
             << endl;

        if (
            corValida(
                grafo,
                verticeAtual,
                cor,
                cores
            )
        ) {

            cout << "Cor valida! Pintando vertice "
                 << verticeAtual
                 << " com cor "
                 << cor
                 << endl;

            cores[verticeAtual] = cor;

            // Mostra estado atual
            cout << "Estado atual: ";

            for (int c : cores) {
                cout << c << " ";
            }

            cout << endl;

            // Próximo vértice
            if (
                backtracking(
                    grafo,
                    verticeAtual + 1,
                    maxCores,
                    cores
                )
            ) {

                return true;
            }

            // Backtracking
            cout << "BACKTRACKING no vertice "
                 << verticeAtual
                 << endl;

            cores[verticeAtual] = -1;
        }
        else {

            cout << "Cor invalida!\n";
        }
    }

    return false;
}

std::vector<int> Coloracao::forcaBruta(Grafo* grafo) {

    int n = grafo->getNumVertices();

    for (int maxCores = 1;
         maxCores <= n;
         maxCores++) {

        vector<int> cores(n, -1);

        if (
            backtracking(
                grafo,
                0,
                maxCores,
                cores
            )
        ) {

            return cores;
        }
    }

    return {};
}