#ifndef ARESTAENCADEADA_H_INCLUDED
#define ARESTAENCADEADA_H_INCLUDED

#include <iostream>

class VerticeEncadeado;

/**
 * @class ArestaEncadeada
 * @brief Representa uma aresta em um grafo utilizando uma estrutura de lista encadeada.
 * 
 * Essa classe é utilizada na implementação do grafo baseado em listas de adjacência.
 * Cada aresta contém referências ao vértice de origem e destino, além de um ponteiro 
 * para a próxima aresta na estrutura encadeada.
 */
class ArestaEncadeada {
private:
    VerticeEncadeado* origem;  ///< Ponteiro para o vértice de origem da aresta.
    VerticeEncadeado* destino; ///< Ponteiro para o vértice de destino da aresta.
    float peso; ///< Peso da aresta (caso o grafo seja ponderado).
    ArestaEncadeada* proximo; ///< Ponteiro para a próxima aresta na lista encadeada.

public:
    /**
     * @brief Construtor da classe ArestaEncadeada.
     * @param origem Ponteiro para o vértice de origem.
     * @param destino Ponteiro para o vértice de destino.
     * @param peso Peso da aresta.
     */
    ArestaEncadeada(VerticeEncadeado* origem, VerticeEncadeado* destino, float peso);

    /**
     * @brief Obtém o vértice de origem da aresta.
     * @return Ponteiro para o vértice de origem.
     */
    VerticeEncadeado* getOrigem() const;

    /**
     * @brief Obtém o vértice de destino da aresta.
     * @return Ponteiro para o vértice de destino.
     */
    VerticeEncadeado* getDestino() const;

    /**
     * @brief Obtém o peso da aresta.
     * @return Peso da aresta.
     */
    float getPeso() const;

    /**
     * @brief Obtém a próxima aresta na lista encadeada.
     * @return Ponteiro para a próxima aresta.
     */
    ArestaEncadeada* getProximo() const;

    /**
     * @brief Define a próxima aresta na lista encadeada.
     * @param novoProximo Ponteiro para a nova aresta seguinte.
     */
    void setProximo(ArestaEncadeada* novoProximo);

    /**
     * @brief Sobrecarga do operador de saída para imprimir a aresta.
     * @param os Stream de saída.
     * @param aresta Aresta a ser impressa.
     * @return Stream de saída atualizado.
     */
    friend std::ostream& operator<<(std::ostream& os, const ArestaEncadeada& aresta);
};

#endif // ARESTAENCADEADA_H_INCLUDED
