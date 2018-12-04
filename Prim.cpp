#include "Prim.hpp"

#include <iostream>

using namespace std;

Prim::Prim(Grafo* g, Vertice* v) {
    this->grafo = g;
    Vertice** vertices = new Vertice*[g->getTamanho()];
    for(int i = 0; i < g->getTamanho(); i++) {
        vertices[i] = nullptr;
    }
    vertices[v->getId()] = v;
    v->inverteValorInserido();
    this->arvore = new Grafo(vertices, g->getTamanhoArestas(), g->getTamanho());

}

Prim::~Prim() {
    delete[] this->arvore;
    delete[] this->grafo;
}

void Prim::adicionaAresta(Aresta* aresta) {
    this->arvore->adicionaAresta(aresta);
}

void Prim::imprimeArvore() {
    this->arvore->imprimeGrafo();
}

