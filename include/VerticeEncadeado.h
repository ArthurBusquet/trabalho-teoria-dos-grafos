#ifndef VERTICEENCADEADO_H_INCLUDED
#define VERTICEENCADEADO_H_INCLUDED

#include <iostream>
#include "ListaEncadeada.h"
#include "ArestaEncadeada.h"

/**
 * @class VerticeEncadeado
 * @brief Representa um vértice em uma estrutura de grafo utilizando listas encadeadas.
 * 
 * Cada vértice possui um identificador único, um peso, um grau (número de conexões) 
 * e uma lista encadeada de conexões (arestas).
 */
class VerticeEncadeado {
private:
    int id; ///< Identificador único do vértice.
    int peso; ///< Peso do vértice (se houver pesos nos vértices).
    int grau; ///< Grau do vértice, ou seja, o número de conexões.
    VerticeEncadeado* proximo; ///< Ponteiro para o próximo vértice na lista encadeada.
    ListaEncadeada<ArestaEncadeada>* conexoes; ///< Lista encadeada de arestas conectadas a este vértice.

public:
    /**
     * @brief Construtor da classe VerticeEncadeado.
     * @param id Identificador do vértice.
     * @param peso Peso do vértice.
     */
    VerticeEncadeado(int id, int peso);

    /**
     * @brief Obtém o identificador do vértice.
     * @return Identificador do vértice.
     */
    int getId() const;

    /**
     * @brief Obtém o peso do vértice.
     * @return Peso do vértice.
     */
    int getPeso() const;

    /**
     * @brief Obtém o grau do vértice (número de conexões).
     * @return Grau do vértice.
     */
    int getGrau() const;

    /**
     * @brief Obtém o próximo vértice na lista encadeada.
     * @return Ponteiro para o próximo vértice.
     */
    VerticeEncadeado* getProximo() const;

    /**
     * @brief Define o próximo vértice na lista encadeada.
     * @param novoProximo Ponteiro para o novo próximo vértice.
     */
    void setProximo(VerticeEncadeado* novoProximo);

    /**
     * @brief Cria uma conexão entre este vértice e outro vértice destino.
     * @param verticeDestino Ponteiro para o vértice de destino.
     * @param pesoAresta Peso da aresta entre os vértices.
     */
    void setConexao(VerticeEncadeado* verticeDestino, int pesoAresta);

    /**
     * @brief Obtém a primeira conexão (aresta) do vértice.
     * @return Ponteiro para a primeira aresta conectada a este vértice.
     */
    ArestaEncadeada* getPrimeiraConexao();

    /**
     * @brief Obtém a lista de conexões (arestas) do vértice.
     * @return Ponteiro para a lista encadeada de arestas.
     */
    ListaEncadeada<ArestaEncadeada>* getConexoes();

    /**
     * @brief Define a lista de conexões (arestas) do vértice.
     * @param novasConexoes Ponteiro para a nova lista de conexões.
     */
    void setConexoes(ListaEncadeada<ArestaEncadeada>* novasConexoes);

    /**
     * @brief Sobrecarga do operador de saída para exibir informações do vértice.
     * @param os Fluxo de saída.
     * @param vertice Vértice a ser exibido.
     * @return Fluxo de saída atualizado.
     */
    friend std::ostream& operator<<(std::ostream& os, const VerticeEncadeado& vertice);

    /**
     * @brief Remove uma conexão específica deste vértice para outro vértice.
     * @param destino Ponteiro para o vértice de destino.
     * @return 1 se a conexão foi removida com sucesso, 0 caso contrário.
     */
    int removeConexao(VerticeEncadeado* destino);

    /**
     * @brief Obtém uma conexão específica entre dois vértices.
     * @param origem Identificador do vértice de origem.
     * @param destino Identificador do vértice de destino.
     * @return Ponteiro para a aresta correspondente ou nullptr se não existir.
     */
    ArestaEncadeada* getConexao(int origem, int destino);
};

#endif // VERTICEENCADEADO_H_INCLUDED
