#include "Vertice.hpp"

Vertice::Vertice(int id, double coordenadaX, double coordenadaY) {
    this->id = id;
    this->coordenadaX = coordenadaX;
    this->coordenadaY = coordenadaY;
    this->inseridoNaArvore = false;
}

int Vertice::getId(){
    return this->id;
}
double Vertice::getCoordenadaX(){
    return this->coordenadaX;
}
double Vertice::getCoordenadaY(){
    return this->coordenadaY;
}

void Vertice::inverteValorInserido() {
    this->inseridoNaArvore = !(this->inseridoNaArvore);
}

bool Vertice::estaInserido() {
    return this->inseridoNaArvore;
}