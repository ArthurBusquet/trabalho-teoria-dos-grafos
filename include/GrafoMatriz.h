#ifndef GRAFO_MATRIZ_H_INCLUDED
#define GRAFO_MATRIZ_H_INCLUDED

#include "Grafo.h"
#include <string>

using namespace std;

const int TAMANHO_INICIAL = 10; ///< Define o tamanho inicial da matriz de adjacência.

/**
 * @class GrafoMatriz
 * @brief Implementação de um grafo utilizando matriz de adjacência.
 * 
 * Esta classe herda da classe abstrata `Grafo` e implementa suas funcionalidades 
 * usando uma matriz 2D para armazenar as conexões entre os vértices.
 */
class GrafoMatriz : public Grafo {
private:
    int** Matriz; ///< Matriz 2D de adjacência para representar o grafo.
    int* MatrizLinear; ///< Matriz linear de adjacência para grafos não direcionados.
    int* VetorPesosVertices; ///< Vetor que armazena os pesos dos vértices.
    int tamanhoAtual; ///< Tamanho atual da matriz de adjacência.
    int tamanhoAtualLinear; ///< Tamanho atual da matriz linear.

public:
    /**
     * @brief Construtor da classe GrafoMatriz.
     * 
     * Inicializa a matriz de adjacência e o vetor de pesos dos vértices.
     */
    GrafoMatriz();

    /**
     * @brief Destrutor da classe GrafoMatriz.
     * 
     * Libera a memória alocada para a matriz de adjacência e demais estruturas.
     */
    virtual ~GrafoMatriz();

    /**
     * @brief Redimensiona a matriz de adjacência para acomodar novos vértices.
     */
    void redimensionarMatriz();

    /**
     * @brief Redimensiona a matriz linear de adjacência para grafos não direcionados.
     */
    void redimensionarMatrizLinear();

    /**
     * @brief Calcula o índice correspondente na matriz linear para uma aresta.
     * @param origem Vértice de origem da aresta.
     * @param destino Vértice de destino da aresta.
     * @return Índice na matriz linear correspondente à aresta.
     */
    int calcularIndiceLinear(int origem, int destino);

    /**
     * @brief Obtém o peso da aresta entre dois vértices.
     * @param origem Vértice de origem.
     * @param destino Vértice de destino.
     * @return Peso da aresta ou -1 se não existir.
     */
    int get_aresta(int origem, int destino) override;

    /**
     * @brief Obtém o peso de um vértice.
     * @param vertice Identificador do vértice.
     * @return Peso do vértice.
     */
    int get_vertice(int vertice) override;

    /**
     * @brief Retorna o número de vizinhos de um vértice.
     * @param vertice Identificador do vértice.
     * @return Número de vizinhos do vértice.
     */
    int get_vizinhos(int vertice) override;

    /**
     * @brief Define o peso de um vértice.
     * @param id Identificador do vértice.
     * @param peso Novo peso do vértice.
     */
    void set_vertice(int id, float peso) override;

    /**
     * @brief Define o peso de uma aresta existente.
     * @param origem Vértice de origem.
     * @param destino Vértice de destino.
     * @param peso Novo peso da aresta.
     */
    void set_aresta(int origem, int destino, float peso) override; 

    /**
     * @brief Adiciona uma nova aresta ao grafo.
     * @param origem Vértice de origem.
     * @param destino Vértice de destino.
     * @param peso Peso da aresta.
     */
    void nova_aresta(int origem, int destino, int peso);

    /**
     * @brief Adiciona um novo vértice ao grafo.
     * @param peso Peso do novo vértice.
     */
    void novo_no(int peso) override;  

    /**
     * @brief Remove um vértice do grafo e todas suas conexões.
     * @param vertice Identificador do vértice a ser removido.
     */
    void deleta_no(int vertice) override;

    /**
     * @brief Remove todas as arestas direcionadas associadas a um vértice.
     * @param vertice Identificador do vértice.
     */
    void deleta_arestas_direcionadas(int vertice);

    /**
     * @brief Remove todas as arestas não direcionadas associadas a um vértice.
     * @param vertice Identificador do vértice.
     */
    void deleta_arestas_nao_direcionadas(int vertice);

    /**
     * @brief Reorganiza a matriz de adjacência após a remoção de um vértice.
     * @param vertice Identificador do vértice removido.
     */
    void reorganiza_matriz(int vertice);

    /**
     * @brief Reorganiza o vetor de pesos dos vértices após a remoção de um vértice.
     * @param vertice Identificador do vértice removido.
     */
    void reorganiza_vetor_pesos(int vertice);

    /**
     * @brief Remove uma aresta do grafo.
     * @param vertice1 Identificador do primeiro vértice.
     * @param vertice2 Identificador do segundo vértice.
     */
    void deleta_aresta(int vertice1, int vertice2) override;
    
};

#endif  // GRAFO_MATRIZ_H_INCLUDED
