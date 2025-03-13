#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"
#include "Cluster.h"

#include <iostream>

using namespace std;

class GrafoLista : public Grafo
{
private:
    ListaEncadeada<VerticeEncadeado> *vertices;
    ListaEncadeada<ArestaEncadeada> *arestas;
    VerticeEncadeado *get_vertice_encadeado(int id);
    void buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados);
    //ListaEncadeada<Cluster>* clusters;
    mutable ListaEncadeada<Cluster>* clusters;

public:
    GrafoLista();

    int get_vertice(int id) override;
    int get_aresta(int idOrigem, int idDestino) override;
    void set_vertice(int id, float peso) override;
    void set_aresta(int origem, int destino, float peso) override;
    void nova_aresta(int origem, int destino, int peso) override;
  
    
    void deleta_aresta(int vertice1, int vertice2) override;
    

    int get_vizinhos(int vertice) override;
    void novo_no(int peso) override;  
    void deleta_no(int vertice) override;
    void imprimirClusters() override;
    void imprimir();
    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
