#include <iostream>
#include <vector>
#include <string>
#include "Grafo.h"
#include "GrafoMatriz.h"


using namespace std;

int main()
{
  int optDir, optPond;
  
  cout << "O grafo e direcionado? (1 - Sim, 0 - Nao): ";
  cin >> optDir;
  
  cout << "O grafo e ponderado? (1 - Sim, 0 - Nao): ";
  cin >> optPond;

  // Cria o grafo com base nas escolhas do usuário
  Grafo* grafo = new GrafoMatriz(optDir == 1, optPond == 1);
  int opcao = -1;

  while(opcao != 0)
  {
    cout << "\n======= MENU DO GRAFO =======" << endl;
    cout << "1. Inserir Vertice" << endl;
    cout << "2. Remover Vertice" << endl;
    cout << "3. Inserir Aresta" << endl;
    cout << "4. Remover Aresta" << endl;
    cout << "5. Imprimir Grafo" << endl;
    cout << "6. Verificar se Existe Aresta" << endl;
    cout << "7. Ver Peso da Aresta" << endl;
    cout << "0. Sair" << endl;
    cout << "=============================" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;

    switch(opcao) {
      case 1: {
        string label;
        cout << "Digite o nome (label) do vertice: ";
        cin >> label;
        grafo->inserir(label);
        cout << "Vertice inserido com sucesso!\n";
        break;
      }
      case 2: {
        int indice;
        cout << "Digite o indice do vertice a ser removido: ";
        cin >> indice;
        grafo->removerVertice(indice);
        cout << "Vertice removido!\n";
        break;
      }
      case 3: {
        int origem, destino;
        string label;
        float peso;
        cout << "nome vertice de Origem: "; cin >> label;
        origem = grafo->converterLabel(label);
        cout << "nome vertice de Destino: "; cin >> label;
        destino = grafo->converterLabel(label);
        cout << "Peso da Aresta: "; cin >> peso;
        if(grafo->inserirAresta(origem, destino, peso)) cout << "Aresta inserida!\n";
        else cout << "Falha ao inserir aresta (indices invalidos).\n";
        break;
      }
      case 4: {
        int origem, destino;
        cout << "Indice de Origem: "; cin >> origem;
        cout << "Indice de Destino: "; cin >> destino;
        if(grafo->removerAresta(origem, destino)) cout << "Aresta removida!\n";
        else cout << "Falha ao remover aresta.\n";
        break;
      }
      case 5:
        cout << "\n--- Estrutura do Grafo ---\n";
        grafo->imprimeGrafo();
        break;
      case 6: {
        int origem, destino;
        cout << "Indice de Origem: "; cin >> origem;
        cout << "Indice de Destino: "; cin >> destino;
        if(grafo->existeAresta(origem, destino)) cout << "A aresta existe!\n";
        else cout << "A aresta NAO existe!\n";
        break;
      }
      case 7: {
        int origem, destino;
        cout << "Indice de Origem: "; cin >> origem;
        cout << "Indice de Destino: "; cin >> destino;
        cout << "O peso da aresta e: " << grafo->pesoAresta(origem, destino) << "\n";
        break;
      }
      case 0:
        cout << "Saindo do sistema...\n";
        break;
      default:
        cout << "Opcao invalida. Tente novamente.\n";
    }
  }

  delete grafo;
  return 0;
}
