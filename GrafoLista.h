#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"

#include <iostream>

class GrafoLista : public Grafo {
private:
    ListaEncadeada<VerticeEncadeado>* vertices;
    ListaEncadeada<ArestaEncadeada>* arestas;



public:
    GrafoLista();


    VerticeEncadeado* get_vertice(int id);
    void set_vertice(int id, float peso);

    void set_aresta(int origem, int destino, int peso);

    int get_vizinhos(int id);

    void imprimir();

    int n_conexo() override;

    int get_grau() override;

    void carrega_grafo() override;

    void buscaEmProfundidade(VerticeEncadeado* vertice, bool* visitados);

    void removerAresta(int origem, int destino);
    bool validarRestricoes();

    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
