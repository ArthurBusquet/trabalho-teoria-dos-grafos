#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"

#include <iostream>

using namespace std;

class GrafoLista : public Grafo
{
private:
    ListaEncadeada<VerticeEncadeado> *vertices;
    ListaEncadeada<ArestaEncadeada> *arestas;
    VerticeEncadeado *get_vertice_encadeado(int id);
    void buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados);

public:
    GrafoLista();

    int get_vertice(int id) override;
    int get_aresta(int idOrigem, int idDestino) override;

    void set_vertice(int id, float peso);
    void set_aresta(int origem, int destino, int peso);
    void nova_aresta(int origem, int destino, int peso) override;


    int get_vizinhos(int vertice);

    void imprimir();

    void inicializa_grafo() override;

    // int n_conexo() override
    // {
    //     return 1;
    // };

    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
