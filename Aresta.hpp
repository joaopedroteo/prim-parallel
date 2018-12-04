#ifndef ARESTA_HPP
#define ARESTA_HPP 1

#include "Vertice.hpp"

class Aresta {
private:
    Vertice* vertice1;
    Vertice* vertice2;
    double peso;
    bool inseridaNaArvore;
public:
    Aresta(Vertice* v1, Vertice* v2, double peso);
    ~Aresta();
    Vertice* getVertice1();
    Vertice* getVertice2();
    void inverteValorInserido();
    bool estaInserida();
    double getPeso();
};

#endif