#ifndef LE_ARQUIVO_HPP
#define LE_ARQUIVO_HPP 1

#include <string>
#include "Vertice.hpp"
#include "Aresta.hpp"

using namespace std;

class LeArquivo {
private:
    Vertice** vertices;
    Aresta** arestas;
    int numeroDeVertices;
    int numeroDeArestas;
public:
    LeArquivo(char* nomeArquivo);
    ~LeArquivo();
    Vertice** getVertices();
    Aresta** getArestas();
    int getNumeroVertices();
    int getNumeroArestas();
    double calculaDistanciaEuclidiana(Vertice* v1, Vertice* v2);
    void imprimeDadosArquivo();
};

#endif