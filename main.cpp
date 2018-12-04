#include <iostream>
#include "LeArquivo.hpp"
#include "Grafo.hpp"
#include "Prim.hpp"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "Numero invalido de argumentos" << endl;
        return 1;
    }
    char* nomeArquivo = argv[1];
    LeArquivo* leArquivo = new LeArquivo(nomeArquivo);

    leArquivo->imprimeDadosArquivo();

    Grafo* grafo = new Grafo(leArquivo->getArestas(), leArquivo->getVertices(), leArquivo->getNumeroArestas(), leArquivo->getNumeroVertices());
    grafo->imprimeGrafo();

    Vertice* verticeInicial = leArquivo->getVertices()[0];
    Prim* prim = new Prim(grafo, verticeInicial);
    prim->adicionaAresta(leArquivo->getArestas()[0]);
    prim->adicionaAresta(leArquivo->getArestas()[7]);
    prim->imprimeArvore();

    return 0;
}