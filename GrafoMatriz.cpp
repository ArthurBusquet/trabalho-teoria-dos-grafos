#include "GrafoMatriz.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

GrafoMatriz::GrafoMatriz()
{
}

GrafoMatriz::~GrafoMatriz()
{
}

void GrafoMatriz::inicializa_grafo()
{
    ifstream arquivo("Grafo.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }

    if (eh_direcionado()) {
        for (int i = 0; i < get_ordem(); ++i) {
            for (int j = 0; j < get_ordem(); ++j) {
                Matriz[i][j] = 0;
            }
        }
    } else {
        for (int i = 0; i < (get_ordem() * (get_ordem() + 1)) / 2; ++i) {
            MatrizLinear[i] = 0;
        }
    }

    if (vertice_ponderado()) {
        for (int i = 0; i < get_ordem(); ++i) {
            arquivo >> VetorPesosVertices[i];
        }
    }

    int origem, destino, peso = 1;
    while (arquivo >> origem >> destino) {
        if (aresta_ponderada()) {
            arquivo >> peso;
        }

        if (eh_direcionado()) {
            Matriz[origem - 1][destino - 1] = peso;
        } else {
            int indice = calcularIndiceLinear(origem, destino);
            MatrizLinear[indice] = peso;
        }
    }
    arquivo.close();
}

int GrafoMatriz::calcularIndiceLinear(int origem, int destino) {
    if (origem <= destino) {
        return (destino * (destino - 1)) / 2 + origem - 1;
    }
    return (origem * (origem - 1)) / 2 + destino - 1;
}

int GrafoMatriz::get_aresta(int origem, int destino) {
    if (eh_direcionado()) {
        return Matriz[origem - 1][destino - 1];
    } else {
        int indice = calcularIndiceLinear(origem, destino);
        return MatrizLinear[indice];
    }
}

int GrafoMatriz::get_vertice(int origem) {
    if (vertice_ponderado()) {
        return VetorPesosVertices[origem - 1];
    }
    return 1;
}

int GrafoMatriz::get_vizinhos(int vertice) {
    int qtdVizinhos = 0;
    if (eh_direcionado()) {
        for (int i = 0; i < get_ordem(); i++) {
            if (Matriz[vertice][i] != 0) {
                qtdVizinhos++;
            }
        }
    } else {
        for (int i = 0; i < get_ordem(); i++) {
            if (i == vertice) continue;

            int index = calcularIndiceLinear(vertice, i);

            if (MatrizLinear[index] != 0) {
                qtdVizinhos++;
            }
        }
    }
    return qtdVizinhos;
}
