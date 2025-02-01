#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

class GrafoMatriz : public Grafo {
private:
    static int** Matriz;                            //Aloca Matriz Dinamicamente 
    static int*  MatrizLinear;                      //Aloca vetor Matriz Linear Dinamicamente
    static int*  VetorPesosVertices;                //Aloca Vetor Pesos Vertices Dinamicamente

    int ordem;              
    bool direcionado;
    bool vtp;
    bool atp;
public:

    void inicializa_matrizes(bool direcionado);
    int calcularIndiceLinear(int origem, int destino);
    void carrega_grafo_matriz();
    
};

#endif  // GRAFOLISTA_H_INCLUDED