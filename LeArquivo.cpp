#include "LeArquivo.hpp"
#include <fstream>
#include <cmath>
#include <iostream>

using namespace std;

LeArquivo::LeArquivo(char* nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if(arquivo.good()) {
        arquivo >> this->numeroDeVertices;
        this->vertices = new Vertice*[this->numeroDeVertices];
        for(int i = 0; i < this->numeroDeVertices and arquivo.good(); i++) {
            int id;
            double coordenadaX;
            double coordenadaY;
            double lixo;
            arquivo >> id >> coordenadaX >> coordenadaY;
            arquivo >> lixo;
            arquivo >> lixo;
            arquivo >> lixo;

            Vertice* vertice = new Vertice(id, coordenadaX, coordenadaY);
            this->vertices[i] = vertice;
        }
        arquivo >> this->numeroDeArestas;
        this->arestas = new Aresta*[this->numeroDeArestas];
        for(int i = 0; i < this->numeroDeArestas and arquivo.good(); i++) {
            int idVertice1;
            int idVertice2;
            arquivo >> idVertice1 >> idVertice2;
            Vertice* v1 = this->vertices[idVertice1];
            Vertice* v2 = this->vertices[idVertice2];
            double distancia = this->calculaDistanciaEuclidiana(v1, v2);
            Aresta* aresta = new Aresta(v1, v2, distancia);
            this->arestas[i] = aresta;
            
        }
    }
    arquivo.close();
}

LeArquivo::~LeArquivo(){
    for(int i = 0; i < this->numeroDeArestas; i++) {
        delete this->arestas[i];
    }
    delete[] this->arestas;
    delete[] this->vertices;
}

double LeArquivo::calculaDistanciaEuclidiana(Vertice* v1, Vertice* v2) {
    return (sqrt(pow(v1->getCoordenadaX() - v2->getCoordenadaX(), 2.0) + pow(v1->getCoordenadaY() - v2->getCoordenadaY(), 2.0)));
}

void LeArquivo::imprimeDadosArquivo() {
    cout << "vertices: " << endl;
    for(int i = 0; i < this->numeroDeVertices; i++) {
        cout << this->vertices[i]->getId() << " ";
    }
    cout << endl;
    cout << "arestas: " << endl;
    for(int i = 0; i < this->numeroDeArestas; i++) {
        cout << this->arestas[i]->getVertice1()->getId() << " - " << this->arestas[i]->getVertice2()->getId() << " (" << this->arestas[i]->getPeso() << ") " << endl;
    }
    cout << endl;
    
}

int LeArquivo::getNumeroVertices(){
    return this->numeroDeVertices;
}
int LeArquivo::getNumeroArestas(){
    return this->numeroDeArestas;
}

Vertice** LeArquivo::getVertices(){
    return this->vertices;
}
Aresta** LeArquivo::getArestas(){
    return this->arestas;
}