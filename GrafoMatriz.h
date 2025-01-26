#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

class GrafoMatriz : public Grafo {
private:
    static int** Matriz;                            //Aloca Matriz Dinamicamente 
    static int*  MatrizLinear;                      //Aloca vetor Matriz Linear Dinamicamente
    static int*  VetorPesosVertices;                //Aloca Vetor Pesos Vertices Dinamicamente

    static int ordem;              
    static bool direcionado;
    static bool vtp;
    static bool atp;

public:
    GrafoMatriz();                           //Construtor
    ~GrafoMatriz();                          //Destrutor

    int calcularIndiceLinear(int origem, int destino);
    void inicializarMatrizes(bool direcionado); 

    void carrega_grafo() override;
    int get_grau() override;
    bool eh_completo() override;
    bool eh_bipartido() override;
    int n_conexo() override;
    bool eh_arvore() override;
    bool possui_articulacao() override;
    bool possui_ponte() override;
    
};

#endif  // GRAFOLISTA_H_INCLUDED