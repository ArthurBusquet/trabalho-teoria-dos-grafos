#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"

#include <iostream>

using namespace std;

/**
 * @class GrafoLista
 * @brief Implementação de um grafo usando listas encadeadas.
 * 
 * Esta classe herda da classe abstrata `Grafo` e implementa suas funcionalidades 
 * utilizando listas encadeadas para armazenar os vértices e arestas.
 */
class GrafoLista : public Grafo
{
private:
    ListaEncadeada<VerticeEncadeado> *vertices; ///< Lista encadeada que armazena os vértices do grafo.
    ListaEncadeada<ArestaEncadeada> *arestas; ///< Lista encadeada que armazena as arestas do grafo.

    /**
     * @brief Obtém um vértice encadeado a partir do seu identificador.
     * @param id Identificador do vértice.
     * @return Ponteiro para o vértice encontrado ou nullptr se não existir.
     */
    VerticeEncadeado *get_vertice_encadeado(int id);

    /**
     * @brief Realiza uma busca em profundidade (DFS) no grafo.
     * @param vertice Ponteiro para o vértice inicial da busca.
     * @param visitados Vetor que indica quais vértices já foram visitados.
     */
    void buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados);

public:
    /**
     * @brief Construtor da classe GrafoLista.
     * 
     * Inicializa a estrutura do grafo utilizando listas encadeadas.
     */
    GrafoLista();

    /**
     * @brief Obtém o peso de um vértice.
     * @param id Identificador do vértice.
     * @return Peso do vértice ou -1 se não existir.
     */
    int get_vertice(int id) override;

    /**
     * @brief Obtém o peso da aresta entre dois vértices.
     * @param idOrigem Identificador do vértice de origem.
     * @param idDestino Identificador do vértice de destino.
     * @return Peso da aresta ou -1 se não existir.
     */
    int get_aresta(int idOrigem, int idDestino) override;

    /**
     * @brief Define o peso de um vértice.
     * @param id Identificador do vértice.
     * @param peso Novo peso do vértice.
     */
    void set_vertice(int id, float peso) override;

    /**
     * @brief Define o peso de uma aresta existente.
     * @param origem Identificador do vértice de origem.
     * @param destino Identificador do vértice de destino.
     * @param peso Novo peso da aresta.
     */
    void set_aresta(int origem, int destino, float peso) override;

    /**
     * @brief Adiciona uma nova aresta ao grafo.
     * @param origem Identificador do vértice de origem.
     * @param destino Identificador do vértice de destino.
     * @param peso Peso da aresta.
     */
    void nova_aresta(int origem, int destino, int peso) override;

    /**
     * @brief Remove uma aresta do grafo.
     * @param vertice1 Identificador do primeiro vértice.
     * @param vertice2 Identificador do segundo vértice.
     */
    void deleta_aresta(int vertice1, int vertice2) override;

    /**
     * @brief Obtém o número de vizinhos de um vértice.
     * @param vertice Identificador do vértice.
     * @return Número de vizinhos do vértice.
     */
    int get_vizinhos(int vertice) override;

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
     * @brief Imprime a representação do grafo.
     */
    void imprimir();

    /**
     * @brief Destrutor da classe GrafoLista.
     * 
     * Libera a memória alocada para as listas encadeadas de vértices e arestas.
     */
    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
