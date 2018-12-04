#ifndef GRAFO_HPP
#define GRAFO_HPP 1

#include "Aresta.hpp"
#include "Vertice.hpp"

class Grafo {
private:
    Aresta*** matrizAdjacencia;
    Vertice** vertices;
    int tamanho;
    int tamanhoArestas;
public:
    Grafo(Aresta** arestas, Vertice** vertices, int tamArestas, int tamanho);
    Grafo(Vertice** vertices, int tamArestas, int tamanho);

    ~Grafo();
    void criaAtributos(Vertice** vertices, int tamArestas, int tam);
    Aresta* getAresta(int i, int j);
    Aresta* getAresta(Vertice* v1, Vertice* v2);
    double getPeso(int i, int j);
    double getPeso(Vertice* v1, Vertice* v2);
    int getTamanho();
    int getTamanhoArestas();

    void adicionaAresta(Aresta* aresta);

    void imprimeGrafo();

    Aresta*** getMatriz();
};

#endif