#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

const int TAMANHO_INICIAL = 10; // Começa com 10 vértices

class GrafoMatriz : public Grafo {
private:
static int** Matriz;                            //Aloca Matriz Dinamicamente 
static int*  MatrizLinear;                      //Aloca vetor Matriz Linear Dinamicamente
static int*  VetorPesosVertices;                //Aloca Vetor Pesos Vertices Dinamicamente

int tamanhoAtual;                                   // Tamanho atual da matriz quadrada
int tamanhoAtualLinear;                         // Tamanho atual da matriz linear

void redimensionarMatriz();                     // Redimensiona a matriz quadrada (direcionado)
void redimensionarMatrizLinear();               // Redimensiona a matriz linear (não direcionado)
public:
    GrafoMatriz();
    ~GrafoMatriz();

    void inicializa_grafo() override;
    int calcularIndiceLinear(int origem, int destino);
    int get_aresta(int origem, int destino);
    int get_vertice(int vertice);
    int get_vizinhos(int vertice);
    void nova_aresta(int origem, int destino, int peso) override;
    void novo_no() override;  


    
    
};

#endif  // GRAFO_MATRIZ_H_INCLUDED
