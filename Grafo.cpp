#include "Grafo.hpp"
#include <iostream>

using namespace std;

void Grafo::criaAtributos(Vertice** vertices, int tamArestas, int tam) {
    this->tamanho = tam;
    this->tamanhoArestas = tamArestas;
    this->vertices = vertices;
    this->matrizAdjacencia = new Aresta**[this->tamanho];
    
    for(int i = 0; i < this->tamanho; i++) {
        this->matrizAdjacencia[i] = new Aresta*[this->tamanho];
        
        for(int j = 0; j < this->tamanho; j++) {
            this->matrizAdjacencia[i][j] = nullptr;
        }
    }
}

Grafo::Grafo(Aresta** arestas, Vertice** vertices, int tamArestas, int tam){
    this->criaAtributos(vertices, tamArestas, tam);

    for(int i = 0; i < tamArestas; i++) {
        this->matrizAdjacencia[arestas[i]->getVertice1()->getId()][arestas[i]->getVertice2()->getId()] = arestas[i];
        this->matrizAdjacencia[arestas[i]->getVertice2()->getId()][arestas[i]->getVertice1()->getId()] = arestas[i];
    }
}

Grafo::Grafo(Vertice** vertices, int tamArestas, int tam){
    this->criaAtributos(vertices, tamArestas, tam);
}

Grafo::~Grafo() {
    
    for(int i = 0; i < this->tamanho; i++) {
        for(int j = 0; j < this->tamanho; j++) {
            delete this->matrizAdjacencia[i][j];
        }
        delete[] this->matrizAdjacencia[i];
    }
    delete[] this->matrizAdjacencia;    
}

Aresta* Grafo::getAresta(int i, int j) {
    return this->matrizAdjacencia[i][j];
}

Aresta* Grafo::getAresta(Vertice* v1, Vertice* v2) {
    return this->matrizAdjacencia[v1->getId()][v2->getId()];
}

double Grafo::getPeso(int i, int j) {
    return this->matrizAdjacencia[i][j]->getPeso();
}

double Grafo::getPeso(Vertice* v1, Vertice* v2) {
    return this->matrizAdjacencia[v1->getId()][v2->getId()]->getPeso();
}

int Grafo::getTamanho() {
    return this->tamanho;
}

int Grafo::getTamanhoArestas() {
    return this->tamanhoArestas;
}


void Grafo::adicionaAresta(Aresta* aresta) {
    this->matrizAdjacencia[aresta->getVertice1()->getId()][aresta->getVertice2()->getId()] = aresta;
    this->matrizAdjacencia[aresta->getVertice2()->getId()][aresta->getVertice1()->getId()] = aresta;
    this->vertices[aresta->getVertice1()->getId()] = aresta->getVertice1();
    this->vertices[aresta->getVertice2()->getId()] = aresta->getVertice2();
    aresta->getVertice1()->inverteValorInserido();
    aresta->getVertice2()->inverteValorInserido();
    aresta->inverteValorInserido();
}


void Grafo::imprimeGrafo() {
    cout << "Vertices" << endl;
    for(int i = 0; i < this->tamanho; i++) {
        if (this->vertices[i] != nullptr) {
            cout << this->vertices[i]->getId() << " ";
        }
    }
    cout << endl;
    
    cout << "Matriz" << endl;
    for(int i = 0; i < this->tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            Aresta* aresta = this->matrizAdjacencia[i][j];
            if(aresta != nullptr) {
                cout << aresta->getPeso() << "\t";
            } else {
                cout << "-\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}