#ifndef VERTICEENCADEADO_H_INCLUDED
#define VERTICEENCADEADO_H_INCLUDED

#include <iostream>
#include "ListaEncadeada.h"
#include "ArestaEncadeada.h"

/**
 * @brief A classe VerticeEncadeado representa um vértice em um grafo implementado usando uma lista encadeada.
 * Ela armazena informações sobre o vértice, como seu identificador, peso e grau, e as conexões (arestas) com outros vértices.
 */
class VerticeEncadeado {
private:
    /**
     * @brief Identificador único do vértice.
     */
    int id;

    /**
     * @brief Peso associado ao vértice.
     */
    int peso;

    /**
     * @brief Grau do vértice, que representa o número de conexões (arestas) que ele possui.
     */
    int grau;

    /**
     * @brief Ponteiro para o próximo vértice na lista encadeada.
     */
    VerticeEncadeado* proximo;

    /**
     * @brief Lista de conexões (arestas) que o vértice tem com outros vértices.
     */
    ListaEncadeada<ArestaEncadeada>* conexoes;

public:
    /**
     * @brief Construtor que cria um vértice com um identificador e peso especificados.
     * 
     * @param id Identificador do vértice.
     * @param peso Peso do vértice.
     */
    VerticeEncadeado(int id, int peso);

    /**
     * @brief Obtém o identificador do vértice.
     * 
     * @return O identificador do vértice.
     */
    int getId() const;

    /**
     * @brief Obtém o peso do vértice.
     * 
     * @return O peso do vértice.
     */
    int getPeso() const;

    /**
     * @brief Obtém o grau do vértice, que é o número de conexões (arestas) que ele possui.
     * 
     * @return O grau do vértice.
     */
    int getGrau() const;

    /**
     * @brief Obtém o próximo vértice na lista encadeada.
     * 
     * @return O próximo vértice.
     */
    VerticeEncadeado* getProximo() const;

    /**
     * @brief Define o próximo vértice na lista encadeada.
     * 
     * @param novoProximo Ponteiro para o próximo vértice.
     */
    void setProximo(VerticeEncadeado* novoProximo);

    /**
     * @brief Estabelece uma conexão entre este vértice e outro vértice, criando uma aresta.
     * 
     * @param verticeDestino O vértice de destino da aresta.
     * @param pesoAresta O peso da aresta.
     */
    void setConexao(VerticeEncadeado* verticeDestino, int pesoAresta);

    /**
     * @brief Obtém a primeira conexão (aresta) do vértice.
     * 
     * @return Ponteiro para a primeira aresta conectada a este vértice.
     */
    ArestaEncadeada* getPrimeiraConexao();

    /**
     * @brief Obtém a lista de todas as conexões (arestas) do vértice.
     * 
     * @return Ponteiro para a lista de arestas.
     */
    ListaEncadeada<ArestaEncadeada>* getConexoes();

    /**
     * @brief Define as conexões (arestas) do vértice.
     * 
     * @param novasConexoes Ponteiro para a nova lista de arestas.
     */
    void setConexoes(ListaEncadeada<ArestaEncadeada>* novasConexoes);

    /**
     * @brief Sobrecarga do operador de saída, permitindo a impressão do vértice no formato desejado.
     * 
     * @param os Fluxo de saída.
     * @param vertice O vértice a ser impresso.
     * 
     * @return O fluxo de saída.
     */
    friend std::ostream& operator<<(std::ostream& os, const VerticeEncadeado& vertice);

    /**
     * @brief Remove uma conexão (aresta) entre este vértice e outro vértice de destino.
     * 
     * @param destino O vértice de destino da aresta a ser removida.
     * 
     * @return O peso da aresta removida.
     */
    int removeConexao(VerticeEncadeado* destino);

    /**
     * @brief Obtém uma conexão (aresta) específica entre dois vértices.
     * 
     * @param origem O vértice de origem da aresta.
     * @param destino O vértice de destino da aresta.
     * 
     * @return A aresta encontrada entre os dois vértices.
     */
    ArestaEncadeada* getConexao(int origem, int destino);
};

#endif // VERTICEENCADEADO_H_INCLUDED
