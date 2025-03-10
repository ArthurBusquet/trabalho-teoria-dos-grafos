#include "../include/Cluster.h"

Cluster::Cluster(int id) : id(id), proximo(nullptr) {
    vertices = new ListaEncadeada<VerticeEncadeado>();
}

Cluster::~Cluster() {
    delete vertices;
}

int Cluster::getId() const {
    return id;
}

void Cluster::adicionarVertice(int vertice) {
    vertices->adicionar(new VerticeEncadeado(vertice, 1));  // ✅ Usa `VerticeEncadeado`
}

void Cluster::imprimirCluster() const {
    std::cout << "Cluster " << id << ": ";
    vertices->imprimir();
}

// ✅ Métodos essenciais para `ListaEncadeada<Cluster>`
Cluster* Cluster::getProximo() const {
    return proximo;
}

void Cluster::setProximo(Cluster* novoProximo) {
    proximo = novoProximo;
}