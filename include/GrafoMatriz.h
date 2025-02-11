#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

const int TAMANHO_INICIAL = 10; // Começa com 10 vértices

/**
 * @brief A classe GrafoMatriz implementa a interface da classe abstrata Grafo utilizando uma matriz de adjacência.
 * A classe gerencia tanto grafos direcionados quanto não direcionados, além de permitir a manipulação de pesos de vértices e arestas.
 */
class GrafoMatriz : public Grafo {
private:
    /**
     * @brief Matriz 2D que armazena a adjacência dos vértices.
     */
    int** Matriz;

    /**
     * @brief Matriz linear que armazena a adjacência para grafos não direcionados.
     */
    int* MatrizLinear;

    /**
     * @brief Vetor de pesos dos vértices.
     */
    int* VetorPesosVertices;

    /**
     * @brief Tamanho atual da matriz 2D.
     */
    int tamanhoAtual;

    /**
     * @brief Tamanho atual da matriz linear.
     */
    int tamanhoAtualLinear;

public:
    /**
     * @brief Construtor da classe GrafoMatriz. Inicializa as matrizes e vetores necessários.
     */
    GrafoMatriz();

    /**
     * @brief Destruidor da classe GrafoMatriz. Libera a memória alocada para as matrizes e vetores.
     */
    virtual ~GrafoMatriz();

    /**
     * @brief Método para redimensionar a matriz 2D de adjacência.
     */
    void redimensionarMatriz();

    /**
     * @brief Método para redimensionar a matriz linear de adjacência.
     */
    void redimensionarMatrizLinear();

    /**
     * @brief Método para inicializar o grafo a partir de um arquivo de entrada.
     * Lê os vértices, arestas e pesos do arquivo de dados.
     */
    void inicializa_grafo();

    /**
     * @brief Calcula o índice linear na matriz comprimida para grafos não direcionados.
     * 
     * @param origem O id do vértice de origem.
     * @param destino O id do vértice de destino.
     * @return O índice linear correspondente aos vértices de origem e destino.
     */
    int calcularIndiceLinear(int origem, int destino);

    /**
     * @brief Método para obter o peso de uma aresta entre dois vértices dados seus ids.
     * 
     * @param origem O id do vértice de origem.
     * @param destino O id do vértice de destino.
     * @return O peso da aresta entre os vértices de origem e destino.
     */
    int get_aresta(int origem, int destino) override;

    /**
     * @brief Método para obter o peso de um vértice dado seu id.
     * 
     * @param vertice O id do vértice.
     * @return O peso do vértice correspondente ao id.
     */
    int get_vertice(int vertice) override;

    /**
     * @brief Método para obter o número de vizinhos de um vértice.
     * 
     * @param vertice O id do vértice.
     * @return O número de vizinhos do vértice.
     */
    int get_vizinhos(int vertice) override;

    /**
     * @brief Método para definir o peso de um vértice dado seu id.
     * 
     * @param id O id do vértice.
     * @param peso O peso a ser atribuído ao vértice.
     */
    void set_vertice(int id, float peso) override;

    /**
     * @brief Método para definir o peso de uma aresta entre dois vértices dados seus ids.
     * 
     * @param origem O id do vértice de origem.
     * @param destino O id do vértice de destino.
     * @param peso O peso a ser atribuído à aresta.
     */
    void set_aresta(int origem, int destino, float peso) override;

    /**
     * @brief Método para adicionar uma nova aresta entre dois vértices, verificando se a aresta já existe.
     * 
     * @param origem O id do vértice de origem.
     * @param destino O id do vértice de destino.
     * @param peso O peso da nova aresta.
     */
    void nova_aresta(int origem, int destino, int peso);
};

#endif  // GRAFO_MATRIZ_H_INCLUDED
