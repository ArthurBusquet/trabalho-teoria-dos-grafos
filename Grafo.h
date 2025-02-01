#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "GrafoMatriz.h"

class Grafo {
private:

    bool direcionado, vtp, atp;
    int ordem, origem, destino, peso;

public:
    Grafo() = default;
    virtual ~Grafo() = default;

    virtual void carrega_grafo_matriz() = 0;
    virtual int get_aresta(int origem, int destino) = 0;
    virtual int get_vertice(int vertice) = 0;
    virtual int* get_vizinhos(int vertice) = 0;

    int get_ordem() {
        return ordem;
    };

    void set_ordem(int ordem) {
        this->ordem = ordem;
    };

    void aumenta_ordem() {
        this->ordem++;
    };

    bool eh_direcionado() {
        return direcionado;
    }

    void set_eh_direcionado(bool direcionado) {
        this->direcionado = direcionado;
    };

    bool vertice_ponderado() {
        return vtp;
    }

    void set_vertice_ponderado(bool verticePonderado) {
        this->vtp = verticePonderado;
    };

    bool aresta_ponderada() {
        return atp;
    }

    void set_aresta_ponderada(bool arestaPonderada) {
        this->atp = arestaPonderada;
    };

    void carrega_grafo(bool usa_matriz) {
        ifstream arquivo("Grafo.txt");
        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }

        arquivo >> ordem >> direcionado >> vtp >> atp;
        set_ordem(ordem);
        set_eh_direcionado(direcionado);
        set_vertice_ponderado(vtp);
        set_aresta_ponderada(atp); 

        if(direcionado) {
            carrega_grafo_matriz();
        }
        
    }    




    virtual bool eh_bipartido() = 0;
    virtual int n_conexo() = 0;
    virtual int get_grau() = 0;
    virtual bool eh_completo() = 0;
    virtual bool eh_arvore() = 0;
    virtual bool possui_articulacao() = 0;
    virtual bool possui_ponte() = 0;
    virtual void carrega_grafo() = 0;
    virtual void novo_grafo() = 0;
};


#endif // GRAFO_H_INCLUDED
