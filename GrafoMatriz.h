#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

const int MAX_VERTICES = 100; // Defina um tamanho máximo para o grafo

class GrafoMatriz : public Grafo {
private:
    int Matriz[MAX_VERTICES][MAX_VERTICES];  // Matriz estática para grafos direcionados
    int MatrizLinear[(MAX_VERTICES * (MAX_VERTICES + 1)) / 2]; // Matriz linear estática para grafos não direcionados
    int VetorPesosVertices[MAX_VERTICES];   // Vetor estático para armazenar pesos dos vértices

public:
    GrafoMatriz();
    ~GrafoMatriz();

    void inicializa_grafo() override;
    int calcularIndiceLinear(int origem, int destino);
    int get_aresta(int origem, int destino);
    int get_vertice(int vertice);
    int get_vizinhos(int vertice);
    void imprime_matriz();
};

#endif  // GRAFO_MATRIZ_H_INCLUDED
