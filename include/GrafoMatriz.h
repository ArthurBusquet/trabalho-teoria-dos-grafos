#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

const int TAMANHO_INICIAL = 10; // Começa com 10 vértices

class GrafoMatriz : public Grafo {
private:
    int** Matriz; // Matriz 2D de adjacência
    int* MatrizLinear; // Matriz linear de adjacência para grafos não direcionados
    int* VetorPesosVertices; // Vetor de pesos dos vértices
    int tamanhoAtual;
    int tamanhoAtualLinear;
public:
    GrafoMatriz();
    virtual ~GrafoMatriz();
    void redimensionarMatriz();
    void redimensionarMatrizLinear();
    void inicializa_grafo();
    int calcularIndiceLinear(int origem, int destino);
    int get_aresta(int origem, int destino) override;
    int get_vertice(int vertice) override;
    int get_vizinhos(int vertice) override;
    void set_vertice(int id, float peso) override;
    void set_aresta(int origem, int destino, float peso) override; 
    void nova_aresta(int origem, int destino, int peso);

    void novo_no(int peso) override;  
    void deleta_no(int vertice) override;
    void deleta_arestas_direcionadas(int vertice);
    void deleta_arestas_nao_direcionadas(int vertice);
    void reorganiza_matriz(int vertice);
    void reorganiza_vetor_pesos(int vertice);

    void deleta_aresta(int vertice1, int vertice2) override;
    
};

#endif  // GRAFO_MATRIZ_H_INCLUDED
