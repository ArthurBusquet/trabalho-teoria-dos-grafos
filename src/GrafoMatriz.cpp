#include "../include/GrafoMatriz.h"
#include "../include/Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// GrafoMatriz::GrafoMatriz() {
//     // Inicializa a matriz de adjacência com 0
//     for (int i = 0; i < MAX_VERTICES; i++) {
//         for (int j = 0; j < MAX_VERTICES; j++) {
//             Matriz[i][j] = 0;
//         }
//     }

//     // Inicializa a matriz linear com 0
//     for (int i = 0; i < (MAX_VERTICES * (MAX_VERTICES + 1)) / 2; i++) {
//         MatrizLinear[i] = 0;
//     }

//     // Inicializa o vetor de pesos dos vértices com 0
//     for (int i = 0; i < MAX_VERTICES; i++) {
//         VetorPesosVertices[i] = 0;
//     }
// }

// GrafoMatriz::~GrafoMatriz() {
//     // Como estamos usando arrays estáticos, não há necessidade de deletar manualmente.
//     // Se usássemos alocação dinâmica (new/malloc), liberaríamos a memória aqui com delete/free.
//     cout << "Destruindo GrafoMatriz..." << endl;
// }

GrafoMatriz::GrafoMatriz() {
    tamanhoAtual = TAMANHO_INICIAL;
    tamanhoAtualLinear = (TAMANHO_INICIAL * (TAMANHO_INICIAL + 1)) / 2;

    // Aloca matriz 2D dinamicamente
    Matriz = new int*[tamanhoAtual];
    for (int i = 0; i < tamanhoAtual; i++) {
        Matriz[i] = new int[tamanhoAtual](); // Inicializa com zero
    }

    // Aloca matriz linear dinamicamente
    MatrizLinear = new int[tamanhoAtualLinear](); // Inicializa com zero

    // Inicializa o vetor de pesos dos vértices com 0
    VetorPesosVertices = new int[tamanhoAtual](); // Inicializa com zero
}


GrafoMatriz::~GrafoMatriz() {
    // Libera a memória alocada para a matriz 2D
    for (int i = 0; i < tamanhoAtual; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;

    // Libera a memória alocada para a matriz linear
    delete[] MatrizLinear;

    cout << "Destruindo GrafoMatriz..." << endl;
}

// Método para redimensionar a matriz quadrada
void GrafoMatriz::redimensionarMatriz() {
    int novoTamanho = tamanhoAtual * 2;
    cout << "Redimensionando matriz quadrada para " << novoTamanho << "..." << endl;

    int** novaMatriz = new int*[novoTamanho];
    for (int i = 0; i < novoTamanho; i++) {
        novaMatriz[i] = new int[novoTamanho];
        for (int j = 0; j < novoTamanho; j++) {
            novaMatriz[i][j] = (i < tamanhoAtual && j < tamanhoAtual) ? Matriz[i][j] : 0;
        }
    }

    // Libera matriz antiga
    for (int i = 0; i < tamanhoAtual; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;

    // Atualiza ponteiro e tamanho
    Matriz = novaMatriz;
    tamanhoAtual = novoTamanho;
}

// Método para redimensionar a matriz linear
void GrafoMatriz::redimensionarMatrizLinear() {
    int novoTamanho = (tamanhoAtual * (tamanhoAtual + 1)) / 2;
    cout << "Redimensionando matriz linear para " << novoTamanho << "..." << endl;

    int* novaMatrizLinear = new int[novoTamanho];
    for (int i = 0; i < novoTamanho; i++) {
        novaMatrizLinear[i] = (i < tamanhoAtualLinear) ? MatrizLinear[i] : 0;
    }

    // Libera a matriz linear antiga
    delete[] MatrizLinear;

    // Atualiza ponteiro e tamanho
    MatrizLinear = novaMatrizLinear;
    tamanhoAtualLinear = novoTamanho;
}

void GrafoMatriz::inicializa_grafo() {
    ifstream arquivo("./entradas/Grafo.txt");
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
        return (destino * (destino - 1)) / 2 + origem;
    }
    return (origem * (origem - 1)) / 2 + destino;
}

int GrafoMatriz::get_aresta(int origem, int destino) {
    if (eh_direcionado()) {
        // Para grafos direcionados, basta acessar diretamente
        return Matriz[origem - 1][destino - 1];
    } else {
        // Para grafos não direcionados, garantir que acessamos a mesma posição para origem e destino
        if (origem > destino) {
            std::swap(origem, destino);  // Garante que origem é sempre menor ou igual a destino
        }
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
            // if (Matriz[i][v] != 0 && i != v) vizinhos++; // Contando entradas
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


void GrafoMatriz::nova_aresta(int origem, int destino, int peso) {
    std::cout << "Tentando adicionar aresta entre " << origem << " e " << destino << " com peso " << peso << std::endl;
    
    // Verificando se a aresta já existea
    if (get_aresta(origem, destino) != 0) {
        std::cout << "Aresta entre " << origem << " e " << destino << " já existe!" << std::endl;
        return;
    }

    // Verifica se os índices estão dentro do limite
    if (origem > /*MAX_VERTICES*/ tamanhoAtual || destino > /*MAX_VERTICES*/ tamanhoAtual) {
        std::cerr << "Erro: Índices de vértice estão fora dos limites da matriz!" << std::endl;
        return;
    }

    // Para grafos direcionados
    if (eh_direcionado()) {
        // Adicionando a aresta na posição correta para grafo direcionado
        Matriz[origem - 1][destino - 1] = peso;
        std::cout << "Aresta adicionada na matriz de adjacência!" << std::endl;
    } 
    // Para grafos não direcionados
    else {
        int indice = calcularIndiceLinear(origem, destino);
        MatrizLinear[indice] = peso;
    }
}
