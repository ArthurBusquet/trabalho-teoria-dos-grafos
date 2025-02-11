#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"

#include <iostream>

using namespace std;

/**
 * @brief A classe GrafoLista é uma implementação de grafo que utiliza listas encadeadas para armazenar os vértices e arestas.
 * Ela herda da classe abstrata Grafo e implementa suas funções virtuais para manipulação de vértices e arestas.
 */
class GrafoLista : public Grafo
{
private:
    /**
     * @brief Ponteiro para a lista encadeada que armazena os vértices do grafo.
     */
    ListaEncadeada<VerticeEncadeado> *vertices;

    /**
     * @brief Ponteiro para a lista encadeada que armazena as arestas do grafo.
     */
    ListaEncadeada<ArestaEncadeada> *arestas;

    /**
     * @brief Função auxiliar para obter um vértice encadeado com base no seu id.
     * 
     * @param id O id do vértice a ser buscado.
     * @return Ponteiro para o vértice correspondente ao id.
     */
    VerticeEncadeado *get_vertice_encadeado(int id);

    /**
     * @brief Função auxiliar para realizar uma busca em profundidade a partir de um vértice específico.
     * 
     * @param vertice O vértice de origem para a busca.
     * @param visitados Vetor de controle para verificar quais vértices já foram visitados.
     */
    void buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados);

public:
    /**
     * @brief Construtor da classe GrafoLista. Inicializa as listas de vértices e arestas.
     */
    GrafoLista();

    /**
     * @brief Método para obter o peso de um vértice dado seu id.
     * 
     * @param id O id do vértice.
     * @return O peso do vértice correspondente ao id.
     */
    int get_vertice(int id) override;

    /**
     * @brief Método para obter o peso de uma aresta entre dois vértices dados seus ids.
     * 
     * @param idOrigem O id do vértice de origem.
     * @param idDestino O id do vértice de destino.
     * @return O peso da aresta entre os vértices de origem e destino.
     */
    int get_aresta(int idOrigem, int idDestino) override;

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
     * @brief Método para adicionar uma nova aresta entre dois vértices.
     * Verifica se a aresta já existe e, caso contrário, adiciona a aresta na lista.
     * 
     * @param origem O id do vértice de origem.
     * @param destino O id do vértice de destino.
     * @param peso O peso da nova aresta.
     */
    void nova_aresta(int origem, int destino, int peso) override;

    /**
     * @brief Método para obter o número de vizinhos de um vértice.
     * 
     * @param vertice O id do vértice.
     * @return O número de vizinhos do vértice.
     */
    int get_vizinhos(int vertice) override;

    /**
     * @brief Método para imprimir os vértices e as arestas do grafo, além de informações sobre o grau e componentes conexas.
     */
    void imprimir();

    /**
     * @brief Método para inicializar o grafo a partir de um arquivo de entrada.
     * Lê as informações de vértices, arestas, pesos e outras configurações.
     */
    void inicializa_grafo() override;

    /**
     * @brief Destruidor da classe GrafoLista. Libera a memória alocada para as listas de vértices e arestas.
     */
    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
