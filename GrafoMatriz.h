
#include "Grafo.h" 
#include <vector>
#include <string>


class GrafoMatriz : public Grafo {
private:
    
    std::vector<std::vector<float>> matriz;
    std::vector<std::string> nomesVertices;

public:
    // Construtor
    GrafoMatriz(bool dir, bool pond);

    bool inserir(std::string label) override;
    bool removerVertice(int indice) override;
    std::string labelVertice(int indice) override;
    void imprimeGrafo() override;
    
    bool inserirAresta(int origem, int destino, float peso = 1) override;
    bool removerAresta(int origem, int destino) override;
    bool existeAresta(int origem, int destino) override;
    float pesoAresta(int origem, int destino) override;
    std::vector<int> retornarVizinhos(int vertice) override;

}; 