#include "GrafoMatriz.h"
#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


int** GrafoMatriz::Matriz = nullptr;
int* GrafoMatriz::MatrizLinear = nullptr;

void GrafoMatriz::inicializa_matrizes(bool direcionado) {
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

void GrafoMatriz::carrega_grafo_matriz() {
    ifstream arquivo("Grafo.txt");
        if (!arquivo.is_open()) {
            cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
            return;
        }
    arquivo >> ordem >> direcionado >> vtp >> atp;


    inicializa_matrizes(direcionado);

    int* pesosVertices = nullptr;
    if (vtp) {
        pesosVertices = new int[ordem];
        for (int i = 0; i < ordem; ++i) {
            arquivo >> pesosVertices[i];
        }
    }

    int origem, destino, peso = 1;
    while (arquivo >> origem >> destino) {
        if (atp) {  arquivo >> peso; }

        if (direcionado) {
            Matriz[origem - 1][destino - 1] = peso;
        } else {
            int indice = calcularIndiceLinear(origem, destino);
            MatrizLinear[indice] = peso;
        }
    }
    arquivo.close();
}

int get_aresta(int origem, int destino) {
    if( direcionado) {

    }

}
