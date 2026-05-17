#ifndef LEITORARQUIVO_H
#define LEITORARQUIVO_H

#include "Grafo.h"
#include <string>

class LeitorArquivo {
public:
    
    static Grafo* carregarGrafo(std::string caminho, bool usarMatriz);
};

#endif
