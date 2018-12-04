#ifndef PRIM_HPP
#define PRIM_HPP 1

#include "Grafo.hpp"
#include "Vertice.hpp"
#include "Aresta.hpp"

class Prim {
private:
    Grafo* arvore;
    Grafo* grafo;
public:
    Prim(Grafo* g, Vertice* v);
    // ~Prim();
    void imprimeArvore();
    void adicionaAresta(Aresta* aresta);
};

#endif