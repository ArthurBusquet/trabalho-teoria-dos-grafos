#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

class Grafo {
public:
    Grafo() = default;
    virtual ~Grafo() = default;

    int ordem;
    bool direcionado;
    bool verticePonderado;
    bool arestaPonderada;

    int get_ordem() {
        return ordem;
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
        return verticePonderado;
    }

    void set_vertice_ponderado(bool verticePonderado) {
        this->verticePonderado = verticePonderado;
    };

    bool aresta_ponderada() {
        return arestaPonderada;
    }

    void set_aresta_ponderada(bool arestaPonderada) {
        this->arestaPonderada = arestaPonderada;
    };

    bool eh_completo() {
        for(int i=1;i<=ordem;i++) {
            if(get_vizinhos(i) < ordem - 1)
                return false;
        }
        return true;
    }

    virtual int get_vizinhos(int id) = 0;
    virtual int n_conexo() = 0;
    virtual int get_grau() = 0;
    virtual void carrega_grafo() = 0;
};


#endif // GRAFO_H_INCLUDED
