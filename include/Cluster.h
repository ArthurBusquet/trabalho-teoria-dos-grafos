#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED

#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include <iostream>

class Cluster {
private:
    int id;
    ListaEncadeada<VerticeEncadeado>* vertices;  // ✅ Agora usa `VerticeEncadeado`
    Cluster* proximo;  // ✅ Para compatibilidade com `ListaEncadeada<Cluster>`

public:
    Cluster(int id);
    ~Cluster();

    int getId() const;
    void adicionarVertice(int vertice);
    void imprimirCluster() const;
    ListaEncadeada<VerticeEncadeado>* getVertices();

    // Métodos obrigatórios para a ListaEncadeada funcionar
    Cluster* getProximo() const;
    void setProximo(Cluster* novoProximo);
};

#endif // CLUSTER_H_INCLUDED
