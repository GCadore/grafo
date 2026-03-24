#include <iostream>
#include <string>
#include "Grafo.h"
#include "LeitorArquivo.h"

using namespace std;

int main() {
    string nomeArquivo;
    int tipoEstrutura;

    cout << "=== CARREGAR GRAFO DE ARQUIVO ===" << endl;
    cout << "Digite o nome do arquivo (ex: grafo.txt): ";
    cin >> nomeArquivo;

    cout << "Escolha a representacao (1 - Matriz de Adj., 2 - Lista de Adj.): ";
    cin >> tipoEstrutura;

    // Passo 2: Usar o Leitor para criar o grafo automaticamente
    // O leitor já resolve se o grafo é direcionado ou ponderado lendo o arquivo!
    Grafo* grafo = LeitorArquivo::carregarGrafo(nomeArquivo, tipoEstrutura == 1);

    if (grafo == nullptr) {
        cout << "Erro ao carregar o grafo. Verifique o arquivo." << endl;
        return 1;
    }

    int opcao = -1;
    while(opcao != 0) {
        cout << "\n======= MENU DO GRAFO (MODO ARQUIVO) =======" << endl;
        cout << "1. Imprimir Grafo (Verificar estrutura)" << endl;
        cout << "2. Inserir Aresta (Manual)" << endl;
        cout << "3. Remover Aresta" << endl;
        cout << "4. Verificar se Existe Aresta" << endl;
        cout << "5. Ver Peso da Aresta" << endl;
        cout << "6. Busca em profundidade" << endl;
        cout << "0. Sair" << endl;
        cout << "=============================" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                cout << "\n--- Estrutura Atual ---\n";
                grafo->imprimeGrafo();
                break;
            case 2: {
                int o, d; float p;
                cout << "Origem (id): "; cin >> o;
                cout << "Destino (id): "; cin >> d;
                cout << "Peso: "; cin >> p;
                grafo->inserirAresta(o, d, p);
                break;
            }
            case 3: {
                int o, d;
                cout << "Origem (id): "; cin >> o;
                cout << "Destino (id): "; cin >> d;
                grafo->removerAresta(o, d);
                break;
            }
            case 4: {
                int o, d;
                cout << "Origem (id): "; cin >> o;
                cout << "Destino (id): "; cin >> d;
                if(grafo->existeAresta(o, d)) cout << "Existe!\n";
                else cout << "Nao existe!\n";
                break;
            }
            case 5: {
                int o, d;
                cout << "Origem (id): "; cin >> o;
                cout << "Destino (id): "; cin >> d;
                cout << "Peso: " << grafo->pesoAresta(o, d) << endl;
                break;
            }
            case 6: {
                string label;
                cout << "Digite o nome do vertice inicial: ";
                cin >> label;
                int indice = grafo->converterLabel(label);
                if (indice != -1) {
                    grafo->buscaProfundidade(indice);
                } else {
                    cout << "Vertice nao encontrado!\n";
                }
                break;
            }
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    }

    delete grafo;
    return 0;
}
