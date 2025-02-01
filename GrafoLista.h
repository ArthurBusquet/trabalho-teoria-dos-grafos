#ifndef GRAFOLISTA_H_INCLUDED
#define GRAFOLISTA_H_INCLUDED

#include "Grafo.h"
#include "ListaEncadeada.h"
#include "VerticeEncadeado.h"
#include "ArestaEncadeada.h"

#include <iostream>

using namespace std;

class GrafoLista : public Grafo {
private:
    ListaEncadeada<VerticeEncadeado>* vertices;
    ListaEncadeada<ArestaEncadeada>* arestas;

    VerticeEncadeado* encontraVertice(int id);



public:
    GrafoLista();

    void adicionarVertice(int id, float peso);
    void adicionarAresta(int origem, int destino, int peso);
    void imprimir();

    bool eh_bipartido() override;

    int n_conexo() override;


    bool eh_completo() override;

    bool eh_arvore() override;
    bool possui_articulacao() override;
    bool possui_ponte() override;

    void carrega_grafo() override;
    void novo_grafo() override;
    // void novo_grafo(const std::string& descricaoArquivo) override;

    void buscaEmProfundidade(VerticeEncadeado* vertice, bool* visitados);

    void removerAresta(int origem, int destino);
    bool validarRestricoes();

    ~GrafoLista();
};

#endif // GRAFOLISTA_H_INCLUDED
