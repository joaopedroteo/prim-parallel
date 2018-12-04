#ifndef VERTICE_HPP
#define VERTICE_HPP 1

class Vertice {
private:
    int id;
    double coordenadaX;
    double coordenadaY;
    bool inseridoNaArvore;
public:
    Vertice(int id, double coordenadaX, double coordenadaY);
    int getId();
    double getCoordenadaX();
    double getCoordenadaY();
    bool estaInserido();
    void inverteValorInserido();
};

#endif