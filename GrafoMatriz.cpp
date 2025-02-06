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

    int num_vertices, direcionado, ponderado_vertices, ponderado_arestas;
    arquivo >> num_vertices >> direcionado >> ponderado_vertices >> ponderado_arestas;


    // Lendo os pesos dos vértices, caso o grafo seja ponderado nos vértices.
    if (ponderado_vertices) {
        for (int i = 0; i < num_vertices; ++i) {
            arquivo >> VetorPesosVertices[i];
        }
    }

    // Inicializando a matriz de adjacência.
    if (direcionado) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                Matriz[i][j] = 0;
            }
        }
    } else {
        for (int i = 0; i < (num_vertices * (num_vertices + 1)) / 2; ++i) {
            MatrizLinear[i] = 0;
        }
    }

    // Lendo as arestas do arquivo.
    int origem, destino, peso;
    while (arquivo >> origem >> destino) {
    if (ponderado_arestas) {
        arquivo >> peso;
    } else {
        arquivo >> peso;
        peso = 1; // Arestas não ponderadas têm peso padrão 1
    }

    if (direcionado) {
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
            if (Matriz[vertice - 1][i] != 0) {
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

// void GrafoMatriz::imprime_matriz() {
//     if (eh_direcionado()) {
//         for (int i = 0; i < get_ordem(); ++i) {
//             for (int j = 0; j < get_ordem(); ++j) {
//                 cout << Matriz[i][j] << " ";
//             }
//             cout << endl;
//         }
//     } else {
//         int index = 0;
//         for (int i = 0; i < get_ordem(); ++i) {
//             for (int j = 0; j <= i; ++j) {
//                 cout << MatrizLinear[index++] << " ";
//             }
//             cout << endl;
//         }
//     }
// }
