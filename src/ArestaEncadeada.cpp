#include "../include/ArestaEncadeada.h"
#include "../include/VerticeEncadeado.h"
#include <iostream>

// Construtor da classe ArestaEncadeada
// Este construtor inicializa uma aresta com os vértices origem e destino, além do peso da aresta.
// O ponteiro 'proximo' é inicializado como nullptr, indicando que a aresta não tem próxima conexão no momento.
ArestaEncadeada::ArestaEncadeada(VerticeEncadeado* origem, VerticeEncadeado* destino, float peso)
    : origem(origem), destino(destino), peso(peso), proximo(nullptr) {}

// Método que retorna o vértice de origem da aresta.
VerticeEncadeado* ArestaEncadeada::getOrigem() const {
    return origem;
}

// Método que retorna o vértice de destino da aresta.
VerticeEncadeado* ArestaEncadeada::getDestino() const {
    return destino;
}

// Método que retorna o peso da aresta.
float ArestaEncadeada::getPeso() const {
    return peso;
}

// Método que retorna o próximo ponteiro de uma aresta encadeada (usado para listas de arestas).
ArestaEncadeada* ArestaEncadeada::getProximo() const {
    return proximo;
}

// Método que define o próximo ponteiro para a aresta encadeada, permitindo a formação de uma lista encadeada.
void ArestaEncadeada::setProximo(ArestaEncadeada* novoProximo) {
    proximo = novoProximo;
}

// Sobrecarga do operador << para permitir imprimir a aresta diretamente.
// A impressão inclui o ID do vértice de origem, o ID do vértice de destino e o peso da aresta.
std::ostream& operator<<(std::ostream& os, const ArestaEncadeada& aresta) {
    os << "Origem: " << aresta.getOrigem()->getId()
       << ", Destino: " << aresta.getDestino()->getId()
       << ", Peso: " << aresta.getPeso();
    return os;
}
