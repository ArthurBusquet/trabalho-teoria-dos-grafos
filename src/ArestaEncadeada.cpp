#include "../include/ArestaEncadeada.h"
#include "../include/VerticeEncadeado.h"
#include <iostream>

/**
 * @brief Construtor da classe ArestaEncadeada.
 * 
 * Inicializa uma aresta entre dois vértices com um determinado peso.
 * 
 * @param origem Ponteiro para o vértice de origem da aresta.
 * @param destino Ponteiro para o vértice de destino da aresta.
 * @param peso Peso da aresta.
 */
ArestaEncadeada::ArestaEncadeada(VerticeEncadeado* origem, VerticeEncadeado* destino, float peso)
    : origem(origem), destino(destino), peso(peso), proximo(nullptr) {}

/**
 * @brief Obtém o vértice de origem da aresta.
 * @return Ponteiro para o vértice de origem.
 */
VerticeEncadeado* ArestaEncadeada::getOrigem() const {
    return origem;
}

/**
 * @brief Obtém o vértice de destino da aresta.
 * @return Ponteiro para o vértice de destino.
 */
VerticeEncadeado* ArestaEncadeada::getDestino() const {
    return destino;
}

/**
 * @brief Obtém o peso da aresta.
 * @return Peso da aresta.
 */
float ArestaEncadeada::getPeso() const {
    return peso;
}

/**
 * @brief Obtém o próximo elemento na lista de arestas encadeadas.
 * @return Ponteiro para a próxima aresta na lista encadeada.
 */
ArestaEncadeada* ArestaEncadeada::getProximo() const {
    return proximo;
}

/**
 * @brief Define a próxima aresta na lista encadeada.
 * @param novoProximo Ponteiro para a nova próxima aresta.
 */
void ArestaEncadeada::setProximo(ArestaEncadeada* novoProximo) {
    proximo = novoProximo;
}

/**
 * @brief Sobrecarga do operador de saída para exibir informações da aresta.
 * 
 * Exibe a origem, o destino e o peso da aresta.
 * 
 * @param os Fluxo de saída.
 * @param aresta Aresta a ser exibida.
 * @return Fluxo de saída atualizado.
 */
std::ostream& operator<<(std::ostream& os, const ArestaEncadeada& aresta) {
    os << "Origem: " << aresta.getOrigem()->getId()
       << ", Destino: " << aresta.getDestino()->getId()
       << ", Peso: " << aresta.getPeso();
    return os;
}
