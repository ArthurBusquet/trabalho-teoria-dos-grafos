#include "GrafoMatriz.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void GrafoMatriz::inicializa_matrizes(bool direcionado) {
    if(direcionado) {
        Matriz = new int*[get_ordem()];
        for (int i = 0; i < get_ordem(); ++i) {
            Matriz[i] = new int[get_ordem()]();
        }
    }
    else MatrizLinear = new int[(get_ordem() * (get_ordem() + 1)) / 2]();
}

int GrafoMatriz::calcularIndiceLinear(int origem, int destino) {
    if (origem <= destino) {
        return (destino * (destino - 1)) / 2 + origem - 1;
    }
    return (origem * (origem - 1)) / 2 + destino - 1;
}

void GrafoMatriz::carrega_grafo_matriz() {
    ifstream arquivo("Grafo.txt");
        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }
    // arquivo >>  >> direcionado >> vtp >> atp;


    inicializa_matrizes(eh_direcionado());

    if (vertice_ponderado()) {
        VetorPesosVertices = new int[get_ordem()];
        for (int i = 0; i < get_ordem(); ++i) {
            arquivo >> VetorPesosVertices[i];
        }
    }

    int origem, destino, peso = 1;
    while (arquivo >> origem >> destino) {
        if (aresta_ponderada()) {  arquivo >> peso; }

        if (eh_direcionado()) {
            Matriz[origem - 1][destino - 1] = peso;
        } else {
            int indice = calcularIndiceLinear(origem, destino);
            MatrizLinear[indice] = peso;
        }
    }
    arquivo.close();
}

int GrafoMatriz::get_aresta(int origem, int destino) {
    if(eh_direcionado()) {
        return Matriz[origem - 1][destino - 1];
    }
    else {
        int indice = calcularIndiceLinear(origem, destino);
        return MatrizLinear[indice];
    }
}

int GrafoMatriz::get_vertice(int origem) {
    if(vertice_ponderado()) {
        return VetorPesosVertices[origem - 1];
    }
}

int* GrafoMatriz::get_vizinhos(int vertice) {
    int* vizinhos = new int[get_ordem()];
    int j = 0;
    if( eh_direcionado()) {
        for (int i = 0; i < get_ordem(); i++) {
            if (Matriz[vertice][i] != 0) {
                vizinhos[j] = i;
                j++;
            }
        }
    }
    else {
        for (int i = 0; i < get_ordem(); i++) {
            if (i == vertice) continue;
        
            int index = calcularIndiceLinear(vertice, i);
        
            if (MatrizLinear[index] != 0) {
                vizinhos[j] = i;
                j++;
            }
        }
    }
    return vizinhos;
}


