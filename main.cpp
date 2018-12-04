#include <iostream>
#include "LeArquivo.hpp"
#include "Grafo.hpp"
#include "Aresta.hpp"
#include "Prim.hpp"

#include <mpi.h>

using namespace std;

typedef struct {
    int idV1;
    int idV2;
    int marcadoV1;
    int marcadoV2;
    int marcadoAresta;
    double peso;
} EstruturaModelo;

void criaEstrutura(MPI_Datatype &ESTRUTURA_GRAFO){
    int numeroBlocos = 6;

    int tamanhoBlocos[6] = {1,1,1,1,1,1};

    MPI_Datatype tiposPrimitivos[6] = {MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_INT, MPI_DOUBLE};

    MPI_Aint displacement[6];
    displacement[0] = offsetof(EstruturaModelo, idV1);
    displacement[1] = offsetof(EstruturaModelo, idV2);
    displacement[2] = offsetof(EstruturaModelo, marcadoV1);
    displacement[3] = offsetof(EstruturaModelo, marcadoV2);
    displacement[4] = offsetof(EstruturaModelo, marcadoAresta);
    displacement[5] = offsetof(EstruturaModelo, peso);

    MPI_Type_create_struct(numeroBlocos, tamanhoBlocos, displacement, tiposPrimitivos, &ESTRUTURA_GRAFO);
    int rc = MPI_Type_commit(&ESTRUTURA_GRAFO);

}

EstruturaModelo instanciaEstruturaModelo(Aresta *aresta){
    EstruturaModelo novaEstrutura;
    if (aresta != nullptr){
        novaEstrutura.idV1 = aresta->getVertice1()->getId();
        novaEstrutura.idV2 = aresta->getVertice2()->getId();
        novaEstrutura.marcadoV1 = aresta->getVertice1()->estaInserido();
        novaEstrutura.marcadoV2 = aresta->getVertice2()->estaInserido();
        novaEstrutura.marcadoAresta = aresta->estaInserida();
        novaEstrutura.peso = aresta->getPeso();
    } else {
        novaEstrutura.idV1 = -1;
        novaEstrutura.idV2 = -1;
        novaEstrutura.marcadoV1 = -1;
        novaEstrutura.marcadoV2 = -1;
        novaEstrutura.marcadoAresta = -1;
        novaEstrutura.peso = -1;
    }

    return novaEstrutura;
}


EstruturaModelo** converteMatrizParaEstrutura(Grafo* grafo){    
    int tamanhoGrafo = grafo->getTamanho();

    EstruturaModelo** matrizEstruturaModelo = new EstruturaModelo*[tamanhoGrafo];

    for (int i = 0; i < tamanhoGrafo; i++){
        matrizEstruturaModelo[i] = new EstruturaModelo[tamanhoGrafo];
        for (int j = 0; j < tamanhoGrafo; j++){
            Aresta* aresta = grafo->getAresta(i,j);
            matrizEstruturaModelo[i][j] = instanciaEstruturaModelo(aresta);
        }
    }
    return matrizEstruturaModelo;
}


int main(int argc, char** argv) {
    if(argc < 2) {
        cout << "Numero invalido de argumentos" << endl;
        return 1;
    }

    int ierr, numeroDeProcessos, rank;
    ierr = MPI_Init(&argc, &argv);


    if (ierr != 0){
        cout << "\n";
        cout << "PRIME_MPI - Fatal error!\n";
        cout << "  MPI_Init returned nonzero ierr.\n";
        exit(1);
    }

    ierr = MPI_Comm_size(MPI_COMM_WORLD, &numeroDeProcessos);

    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Datatype ESTRUTURA_GRAFO;

    char* nomeArquivo = argv[1];

    LeArquivo* leArquivo = new LeArquivo(nomeArquivo);
    Grafo* grafo = new Grafo(leArquivo->getArestas(), leArquivo->getVertices(), leArquivo->getNumeroArestas(), leArquivo->getNumeroVertices());
    // grafo->imprimeGrafo();

    Vertice* verticeInicial = leArquivo->getVertices()[0];
    Prim* prim = new Prim(grafo, verticeInicial);

    EstruturaModelo** matrizEstruturaModelo = converteMatrizParaEstrutura(grafo);

    

    criaEstrutura(ESTRUTURA_GRAFO);
    

    int numeroDeColunas = grafo->getTamanho() / numeroDeProcessos;

    int resto = grafo->getTamanho() % numeroDeProcessos;

    int sendCounts[numeroDeProcessos], displs[numeroDeProcessos];

    int acumulador = 0;

    for (int i = 0; i < numeroDeProcessos; i++){
        sendCounts[i] = numeroDeColunas * grafo->getTamanho();
        if (resto > 0){
            sendCounts[i] += grafo->getTamanho();
            resto--;
        }
        
        displs[i] = acumulador;
        acumulador += sendCounts[i];

    }

    EstruturaModelo recvbuf[sendCounts[rank]];
    int recvcount = sendCounts[rank];

    for (int i = 0; i < grafo->getTamanho(); i++){
        for (int j = 0; j < grafo->getTamanho(); j++){
            cout << matrizEstruturaModelo[i][j].idV1 << " ";
        }
        cout << endl;
    }
    cout << "RANK: " << rank<< " " << sendCounts[rank] << " " << displs[rank] << " " << recvbuf << " " << recvcount << " " << endl;
    int rc = MPI_Scatterv(matrizEstruturaModelo, sendCounts, displs, ESTRUTURA_GRAFO, recvbuf, recvcount, ESTRUTURA_GRAFO, 0, MPI_COMM_WORLD);
    cout << sizeof(EstruturaModelo) << endl << "-----" << endl;
    cout << "RANK: " << rank << " " << sendCounts[rank] << " " << displs[rank] << " " << recvbuf << " " << recvcount << " " << endl;
    // cout << recvbuf[0].peso << " RRRR: " << rank << endl;
    cout << sendCounts[rank] << " RANK: " << rank << " --> ";
    cout << displs[rank] << " RANK: " << rank << " --> ";
    cout << sizeof(recvbuf)/sizeof(EstruturaModelo) << " RANK: " << rank << " ";
    if (rank == 0) {
        for (int i = 0; i < sendCounts[rank]; i++){
            cout << "i:" << i << ' ' << recvbuf[i].idV1 << " " << endl;
        }
        cout << endl;
    }

    cout << endl;

    MPI_Type_free(&ESTRUTURA_GRAFO);    
    
    // prim->adicionaAresta(leArquivo->getArestas()[0]);
    // prim->adicionaAresta(leArquivo->getArestas()[7]);
    // prim->imprimeArvore();

    MPI_Finalize();

    return 0;
}



