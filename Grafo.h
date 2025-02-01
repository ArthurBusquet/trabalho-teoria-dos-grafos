#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

class Grafo {
private:
    bool direcionado, vtp, atp;
    int ordem, origem, destino, peso;

public:
    Grafo() = default;
    virtual ~Grafo() = default;

    virtual int get_aresta(int origem, int destino) = 0;
    virtual int get_vertice(int vertice) = 0;
    virtual int get_vizinhos(int vertice) = 0;

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
        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }

        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }

        arquivo >> ordem >> direcionado >> vtp >> atp;
        set_ordem(ordem);
        set_eh_direcionado(direcionado);
        set_vertice_ponderado(vtp);
        set_aresta_ponderada(atp);

       inicializa_grafo();
    }

  // ------------------ Função para calcular o grau do grafo ------------------

    int get_grau() {
        if(!eh_direcionado()) {
            int grauMaximo = 0;

            for (int i = 0; i < ordem; i++) {
                int numVizinhos = get_vizinhos(i);
            
                if (numVizinhos > grauMaximo) {
                    grauMaximo = numVizinhos;
                }
            }
            return grauMaximo;
        }
        else {
            int maxGrauSaida = 0;

            for (int i = 0; i < ordem; i++) {
                int grauSaida = 0;
                
                // Calcula grau de saída
                int numVizinhos = get_vizinhos(i);
                grauSaida = numVizinhos;

                if (grauSaida > maxGrauSaida) {
                    maxGrauSaida = grauSaida;
                }
            }
            return  maxGrauSaida;
        }

    }

    // ------------------ Métodos virtuais puros ------------------
    virtual int n_conexo() = 0;
    virtual void inicializa_grafo() = 0;
};

#endif // GRAFO_H_INCLUDED
