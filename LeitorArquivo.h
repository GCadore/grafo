#ifndef LEITORARQUIVO_H
#define LEITORARQUIVO_H

#include "Grafo.h"
#include <string>

class LeitorArquivo {
public:
    // Esta função recebe o caminho do arquivo e retorna um ponteiro para o Grafo criado
    static Grafo* carregarGrafo(std::string caminho, bool usarMatriz);
};

#endif
