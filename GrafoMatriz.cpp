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

void GrafoMatriz::inicializa_grafo() {
    ifstream arquivo("Grafo.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }

    int num_vertices, direcionado, ponderado_vertices, ponderado_arestas;
    arquivo >> num_vertices >> direcionado >> ponderado_vertices >> ponderado_arestas;

    // Lendo os pesos dos vértices, caso o grafo seja ponderado nos vértices.
    if (ponderado_vertices) {
        int index = 0;
        while (index < num_vertices) {
            arquivo >> VetorPesosVertices[index];
            index = index + 1;
        }
    }

    // Inicializando a matriz de adjacência.
    if (direcionado) {
        int linha = 0;
        while (linha < num_vertices) {
            int coluna = 0;
            while (coluna < num_vertices) {
                Matriz[linha][coluna] = 0;
                coluna = coluna + 1;
            }
            linha = linha + 1;
        }
    } else {
        int index = 0;
        while (index < (num_vertices * (num_vertices + 1)) / 2) {
            MatrizLinear[index] = 0;
            index = index + 1;
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
    if (vertice < 1 || vertice > get_ordem()) {
        cerr << "Vértice inválido!" << endl;
        return -1;
    }

    int vizinhos = 0;
    int v = vertice - 1; // Ajustando para índice 0

    if (eh_direcionado()) {
        // Contar arestas de entrada e saída
        for (int i = 0; i < get_ordem(); i++) {
            if (Matriz[v][i] != 0) vizinhos++; // Contando saídas
            if (Matriz[i][v] != 0 && i != v) vizinhos++; // Contando entradas
        }
    } else {
        // Grafo não direcionado: verificar matriz comprimida
        for (int i = 0; i < get_ordem(); i++) {
            if (i == v) continue; // Evita contar o próprio vértice

            int indice = calcularIndiceLinear(i + 1, vertice);
            if (MatrizLinear[indice] != 0) {
                vizinhos++;
            }
        }
    }

    return vizinhos;
}


void GrafoMatriz::imprime_matriz() {
    if (eh_direcionado()) {
        for (int i = 0; i < get_ordem(); ++i) {
            for (int j = 0; j < get_ordem(); ++j) {
                cout << Matriz[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        int index = 0;
        for (int i = 0; i < get_ordem(); ++i) {
            for (int j = 0; j <= i; ++j) {
                cout << MatrizLinear[index++] << " ";
            }
        }
        cout << endl; // Adiciona uma nova linha ao final da impressão
    }
}
