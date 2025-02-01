#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

class GrafoMatriz : public Grafo {
private:
    int** Matriz;                            //Aloca Matriz 
    int*  MatrizLinear;                      //Aloca vetor Matriz Linear
    int*  VetorPesosVertices;                //Aloca Vetor Pesos Vertices

public:

    void inicializa_matrizes(bool direcionado);
    int calcularIndiceLinear(int origem, int destino);
    void carrega_grafo_matriz();
    int get_aresta(int origem, int destino);
    int get_vertice(int vertice);
    int* get_vizinhos(int vertice);
    
};

#endif  // GRAFOLISTA_H_INCLUDED