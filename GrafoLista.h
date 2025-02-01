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

public:
    GrafoLista();

    int get_vertice(int id) override;
    int get_aresta(int idOrigem, int idDestino) override;

    void set_vertice(int id, float peso);
    void set_aresta(int origem, int destino, int peso);
    

    int get_vizinhos(int id);

    void imprimir();

    void inicializa_grafo() override {};

    void buscaEmProfundidade(VerticeEncadeado *vertice, bool *visitados);

    int n_conexo() override
    {
        return 1;
    };

    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
