#include "GrafoMatriz.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int** GrafoMatriz::Matriz = nullptr;
int* GrafoMatriz::MatrizLinear = nullptr;
int* GrafoMatriz::VetorPesosVertices = nullptr;
int GrafoMatriz::ordem = 0;
bool GrafoMatriz::direcionado = false;
bool GrafoMatriz::vtp = false;
bool GrafoMatriz::atp = false;


GrafoMatriz::GrafoMatriz(){};

GrafoMatriz::~GrafoMatriz() {
    if(direcionado) delete [] VetorPesosVertices;  
    if (Matriz) {
        for (int i = 0; i < ordem; ++i) {
            delete[] Matriz[i];
        }
        delete[] Matriz;
    }
    delete[] MatrizLinear;
}

void GrafoMatriz::inicializarMatrizes(bool direcionado) {
    if(direcionado) {
        Matriz = new int*[ordem];
        for (int i = 0; i < ordem; ++i) {
            Matriz[i] = new int[ordem]();
        }
    }
    else MatrizLinear = new int[(ordem * (ordem + 1)) / 2]();
}

int GrafoMatriz::calcularIndiceLinear(int origem, int destino) {
    if (origem <= destino) {
        return (destino * (destino - 1)) / 2 + origem - 1;
    }
    return (origem * (origem - 1)) / 2 + destino - 1;
}

void GrafoMatriz::carrega_grafo() {
    ifstream arquivo("Grafo.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }

    arquivo >> ordem >> direcionado >> vtp >> atp;

    inicializarMatrizes(direcionado);

    int* pesosVertices = nullptr;
    if (vtp) {
        pesosVertices = new int[ordem];
        for (int i = 0; i < ordem; ++i) {
            arquivo >> pesosVertices[i];
        }
    }

    int origem, destino, peso = 1;
    while (arquivo >> origem >> destino) {
        if (atp) {
            arquivo >> peso;
        }

        if (direcionado) {
            Matriz[origem - 1][destino - 1] = peso;
        } else {
            int indice = calcularIndiceLinear(origem, destino);
            MatrizLinear[indice] = peso;
        }
    }

    arquivo.close();
    if (vertice_ponderado) delete[] pesosVertices;

    //cout << "Grafo carregado com sucesso!" << endl;
}

int GrafoMatriz::get_grau() {
    int grau_maximo = 0;

    if (direcionado) {
        // Grafo direcionado: usa matriz 2D
        for (int i = 0; i < ordem; ++i) {
            int grau = 0;
            for (int j = 0; j < ordem; ++j) {
                if (Matriz[i][j] != 0) grau++;
            }
            grau_maximo = max(grau_maximo, grau);
        }
    } else {
        // Grafo não direcionado: usa matriz linear
        for (int i = 0; i < ordem; ++i) {
            int grau = 0;
            for (int j = 0; j < ordem; ++j) {
                if (i != j) {
                    int indice = calcularIndiceLinear(i + 1, j + 1);
                    if (MatrizLinear[indice] != 0) grau++;
                }
            }
            grau_maximo = max(grau_maximo, grau);
        }
    }
    return grau_maximo;
}

bool GrafoMatriz::eh_completo() {
    if (direcionado) {
        // Grafo direcionado: usa matriz 2D
        for (int i = 0; i < ordem; ++i) {
            for (int j = 0; j < ordem; ++j) {
                if (i != j && Matriz[i][j] == 0) {
                    return false;
                }
            }
        }
    } else {
        // Grafo não direcionado: usa matriz linear
        for (int i = 0; i < ordem; ++i) {
            for (int j = i + 1; j < ordem; ++j) { 
                int indice = calcularIndiceLinear(i + 1, j + 1);
                if (MatrizLinear[indice] == 0) {
                    return false;
                }
            }
        }
    }
    return true;
}
