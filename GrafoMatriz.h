#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

class GrafoMatriz : public Grafo {
private:

    int** Matriz;                            //Aloca Matriz Dinamicamente
    int*  MatrizLinear;                      //Aloca vetor Matriz Linear Dinamicamente
    int*  VetorPesosVertices;                //Aloca Vetor Pesos Vertices Dinamicamente

public:
    GrafoMatriz() {};
    void inicializa_matrizes(bool direcionado);
    int calcularIndiceLinear(int origem, int destino);
    void inicializa_grafo() override;
    int get_aresta(int origem, int destino);
    int get_vertice(int vertice);
    int get_vizinhos(int vertice);
    int n_conexo() override {
        return 1;
    };
    ~GrafoMatriz();

};

#endif  // GRAFOLISTA_H_INCLUDED