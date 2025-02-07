#ifndef ARESTAENCADEADA_H_INCLUDED
#define ARESTAENCADEADA_H_INCLUDED

#include <iostream>

class VerticeEncadeado;

class ArestaEncadeada {
private:
    VerticeEncadeado* origem;
    VerticeEncadeado* destino;
    float peso;
    ArestaEncadeada* proximo;

public:
    ArestaEncadeada(VerticeEncadeado* origem, VerticeEncadeado* destino, float peso);

    VerticeEncadeado* getOrigem() const;
    VerticeEncadeado* getDestino() const;
    float getPeso() const;
    ArestaEncadeada* getProximo() const;
    void setProximo(ArestaEncadeada* novoProximo);

    friend std::ostream& operator<<(std::ostream& os, const ArestaEncadeada& aresta);
};

#endif // ARESTAENCADEADA_H_INCLUDED
