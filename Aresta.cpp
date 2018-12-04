#include "Aresta.hpp"

Aresta::Aresta(Vertice* v1, Vertice* v2, double p) {
    this->vertice1 = v1;
    this->vertice2 = v2;
    this->peso = p;
    this->inseridaNaArvore = false;
}

Aresta::~Aresta(){
    delete this->vertice1;
    delete this->vertice2;
}
Vertice* Aresta::getVertice1(){
    return this->vertice1;
}
Vertice* Aresta::getVertice2(){
    return this->vertice2;
}
double Aresta::getPeso(){
    return this->peso;
}

void Aresta::inverteValorInserido() {
    this->inseridaNaArvore = !(this->inseridaNaArvore);
}

bool Aresta::estaInserida() {
    return this->inseridaNaArvore;
}