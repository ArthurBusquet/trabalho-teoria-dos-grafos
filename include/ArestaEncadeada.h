#ifndef ARESTAENCADEADA_H_INCLUDED
#define ARESTAENCADEADA_H_INCLUDED

#include <iostream>

// A classe ArestaEncadeada representa uma aresta em um grafo, que conecta dois vértices (origem e destino)
// e pode ter um peso associado. Esta classe é usada para representar arestas encadeadas em um grafo baseado
// em listas encadeadas.
class VerticeEncadeado;  // Declaração antecipada da classe VerticeEncadeado (classe de vértices no grafo)

class ArestaEncadeada {
private:
    VerticeEncadeado* origem;   // Ponteiro para o vértice de origem da aresta
    VerticeEncadeado* destino;  // Ponteiro para o vértice de destino da aresta
    float peso;                 // Peso da aresta (pode ser 0 para arestas não ponderadas)
    ArestaEncadeada* proximo;  // Ponteiro para a próxima aresta, caso haja uma lista de arestas encadeadas

public:
    // Construtor que inicializa os valores da aresta (origem, destino e peso).
    // O próximo ponteiro é inicializado como nullptr (sem aresta subsequente).
    ArestaEncadeada(VerticeEncadeado* origem, VerticeEncadeado* destino, float peso);

    // Métodos de acesso (getters) para os membros privados da classe.

    // Retorna o vértice de origem da aresta.
    VerticeEncadeado* getOrigem() const;

    // Retorna o vértice de destino da aresta.
    VerticeEncadeado* getDestino() const;

    // Retorna o peso da aresta.
    float getPeso() const;

    // Retorna o ponteiro para a próxima aresta na lista de arestas encadeadas.
    ArestaEncadeada* getProximo() const;

    // Define o ponteiro da próxima aresta na lista encadeada de arestas.
    void setProximo(ArestaEncadeada* novoProximo);

    // Sobrecarga do operador de fluxo (<<) para permitir a impressão das arestas
    // A impressão inclui as informações de origem, destino e peso da aresta.
    friend std::ostream& operator<<(std::ostream& os, const ArestaEncadeada& aresta);
};

#endif // ARESTAENCADEADA_H_INCLUDED