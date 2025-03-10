#include "../include/GrafoMatriz.h"
#include "../include/Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int TAMANHO_FIXO = 10000; // Define um tamanho fixo grande para a matriz

GrafoMatriz::GrafoMatriz()
{
    tamanhoAtual = TAMANHO_FIXO;
    size_t tamanhoAtualLinear = ((size_t)TAMANHO_FIXO * (TAMANHO_FIXO + 1)) / 2;

    // Aloca matriz 2D estaticamente
    Matriz = new int*[tamanhoAtual];
    for (int i = 0; i < tamanhoAtual; i++)
    {
        Matriz[i] = new int[tamanhoAtual](); // Inicializa com zero
    }

    // Aloca matriz linear estaticamente
    MatrizLinear = new int[tamanhoAtualLinear](); // Inicializa com zero

    // Inicializa o vetor de pesos dos vértices com 0
    VetorPesosVertices = new int[tamanhoAtual](); // Inicializa com zero
}

GrafoMatriz::~GrafoMatriz()
{
    // Libera a memória alocada para a matriz 2D
    for (int i = 0; i < tamanhoAtual; i++)
    {
        delete[] Matriz[i]; // Libera cada linha da matriz
    }
    delete[] Matriz; // Libera o array de ponteiros para as linhas da matriz

    // Libera a memória alocada para a matriz linear
    delete[] MatrizLinear; // Libera o vetor que armazena a matriz linear

    cout << "Destruindo GrafoMatriz..." << endl;
}

// Método para redimensionar a matriz quadrada
// void GrafoMatriz::redimensionarMatriz() {
//     int novoTamanho = tamanhoAtual * 2;  // Dobra o tamanho da matriz
//     cout << "Redimensionando matriz quadrada para " << novoTamanho << "..." << endl;

//     // Cria uma nova matriz maior
//     int** novaMatriz = new int*[novoTamanho];
//     for (int i = 0; i < novoTamanho; i++) {
//         novaMatriz[i] = new int[novoTamanho];
//         for (int j = 0; j < novoTamanho; j++) {
//             novaMatriz[i][j] = (i < tamanhoAtual && j < tamanhoAtual) ? Matriz[i][j] : 0;
//         }
//     }

//     // Libera a matriz antiga
//     for (int i = 0; i < tamanhoAtual; i++) {
//         delete[] Matriz[i];
//     }
//     delete[] Matriz;  // Libera o array de ponteiros para as linhas da matriz antiga

//     // Atualiza ponteiro e tamanho
//     Matriz = novaMatriz;  // A nova matriz é agora a matriz ativa
//     tamanhoAtual = novoTamanho;  // Atualiza o tamanho da matriz
// }

// Método para redimensionar a matriz linear
// void GrafoMatriz::redimensionarMatrizLinear() {
//     int novoTamanho = (tamanhoAtual * (tamanhoAtual + 1)) / 2;  // Calcula o novo tamanho para a matriz linear
//     cout << "Redimensionando matriz linear para " << novoTamanho << "..." << endl;

//     // Cria a nova matriz linear
//     int* novaMatrizLinear = new int[novoTamanho];
//     for (int i = 0; i < novoTamanho; i++) {
//         novaMatrizLinear[i] = (i < tamanhoAtualLinear) ? MatrizLinear[i] : 0;
//     }

//     // Libera a matriz linear antiga
//     delete[] MatrizLinear;

//     // Atualiza ponteiro e tamanho
//     MatrizLinear = novaMatrizLinear;  // A nova matriz linear é agora a matriz ativa
//     tamanhoAtualLinear = novoTamanho;  // Atualiza o tamanho da matriz linear
// }

// Método para inicializar o grafo a partir de um arquivo
void GrafoMatriz::inicializa_grafo()
{
    ifstream arquivo("./entradas/Grafo.txt");
    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo Grafo.txt" << endl;
        return;
    }

    int num_vertices, direcionado, ponderado_vertices, ponderado_arestas;
    arquivo >> num_vertices >> direcionado >> ponderado_vertices >> ponderado_arestas;

    // Lendo os pesos dos vértices, caso o grafo seja ponderado nos vértices
    if (ponderado_vertices)
    {
        int index = 0;
        while (index < num_vertices)
        {
            arquivo >> VetorPesosVertices[index];
            index = index + 1; // Preenche o vetor com os pesos dos vértices
        }
    }

    // Inicializando a matriz de adjacência
    if (direcionado)
    {
        int linha = 0;
        while (linha < num_vertices)
        {
            int coluna = 0;
            while (coluna < num_vertices)
            {
                Matriz[linha][coluna] = 0; // Inicializa todas as entradas como zero
                coluna = coluna + 1;
            }
            linha = linha + 1;
        }
    }
    else
    {
        int index = 0;
        while (index < (num_vertices * (num_vertices + 1)) / 2)
        {
            MatrizLinear[index] = 0; // Inicializa a matriz linear com zero
            index = index + 1;
        }
    }

    // Lendo as arestas do arquivo
    int origem, destino, peso;
    while (arquivo >> origem >> destino)
    {
        if (ponderado_arestas)
        {
            arquivo >> peso;
        }
        else
        {
            arquivo >> peso;
            peso = 1; // Arestas não ponderadas têm peso padrão 1
        }

        if (direcionado)
        {
            Matriz[origem - 1][destino - 1] = peso; // Adiciona aresta na matriz para grafos direcionados
        }
        else
        {
            int indice = calcularIndiceLinear(origem, destino);
            MatrizLinear[indice] = peso; // Adiciona aresta na matriz linear para grafos não direcionados
        }
    }
    arquivo.close(); // Fecha o arquivo
}

// Método para calcular o índice linear da matriz comprimida
int GrafoMatriz::calcularIndiceLinear(int origem, int destino)
{
    // Garante que origem <= destino
    if (origem > destino)
    {
        std::swap(origem, destino);
    }
    // Fórmula correta para índice linear em uma matriz triangular inferior
    return (destino * (destino - 1)) / 2 + origem;
}

// Método para obter o peso da aresta entre dois vértices
int GrafoMatriz::get_aresta(int origem, int destino)
{
    if (origem < 1 || destino < 1 || origem > tamanhoAtual || destino > tamanhoAtual)
    {
        cerr << "Erro: Índices fora dos limites da matriz!" << endl;
        return -1; // Retorno de erro se os índices estiverem fora dos limites
    }

    if (eh_direcionado())
    {
        return Matriz[origem - 1][destino - 1]; // Para grafos direcionados, retorna diretamente da matriz
    }
    else
    {
        if (origem > destino)
        {
            std::swap(origem, destino); // Garante que origem é sempre menor ou igual a destino
        }
        int indice = calcularIndiceLinear(origem, destino);
        return MatrizLinear[indice]; // Para grafos não direcionados, retorna da matriz comprimida
    }
}

// Método para definir o peso de um vértice
void GrafoMatriz::set_vertice(int id, float peso)
{
    if (!vertice_ponderado()) // Verifica se o grafo é ponderado
        peso = 0;             // Se não for ponderado, atribui peso 0

    VetorPesosVertices[id - 1] = peso; // Define o peso do vértice
}

// Método para definir o peso de uma aresta entre dois vértices
void GrafoMatriz::set_aresta(int origem, int destino, float peso)
{

    if (!aresta_ponderada()) // Verifica se o grafo é ponderado
        peso = 1;            // Se não for ponderado, atribui peso 0

    if (eh_direcionado())
    {
        Matriz[origem][destino] = peso; // Para grafos direcionados, adiciona na matriz de adjacência
    }
    else
    {
        // Certifique-se de que origem é sempre menor ou igual a destino
        if (origem > destino)
        {
            std::swap(origem, destino); // Troca origem e destino para garantir a ordem
        }
        int indice = calcularIndiceLinear(origem, destino);
        MatrizLinear[indice] = peso; // Para grafos não direcionados, adiciona na matriz comprimida
    }

    std::cout << "Matriz Triangular Inferior:" << std::endl;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j <= i; j++) {
            // Calcula o índice linear para a posição (i, j)
            int indice = calcularIndiceLinear(j, i);
            std::cout << MatrizLinear[indice] << " ";
        }
        std::cout << std::endl;
    }
}

// Método para obter o peso de um vértice
int GrafoMatriz::get_vertice(int origem)
{
    if (vertice_ponderado())
    {
        return VetorPesosVertices[origem - 1]; // Retorna o peso do vértice se ponderado
    }
    return 1; // Caso não seja ponderado, retorna peso 1 por padrão
}

// Método para obter o número de vizinhos de um vértice
int GrafoMatriz::get_vizinhos(int vertice)
{
    if (vertice < 1 || vertice > get_ordem())
    {
        cerr << "Vértice inválido!" << endl;
        return -1; // Retorno de erro se o vértice for inválido
    }

    int vizinhos = 0;
    int v = vertice - 1; // Ajustando para índice 0

    if (eh_direcionado())
    {
        // Contar arestas de entrada e saída
        for (int i = 0; i < get_ordem(); i++)
        {
            if (Matriz[v][i] != 0)
                vizinhos++; // Contando saídas
        }
    }
    else
    {
        // Para grafos não direcionados, verificar matriz comprimida
        for (int i = 0; i < get_ordem(); i++)
        {
            if (i == v)
                continue; // Evita contar o próprio vértice

            int indice = calcularIndiceLinear(i + 1, vertice);
            if (MatrizLinear[indice] != 0)
            {
                vizinhos++; // Conta os vizinhos
            }
        }
    }

    return vizinhos;
}

// Método para adicionar uma nova aresta entre dois vértices
void GrafoMatriz::nova_aresta(int origem, int destino, int peso)
{
    std::cout << "Tentando adicionar aresta entre " << origem << " e " << destino << " com peso " << peso << std::endl;

    // Verificando se a aresta já existe
    if (get_aresta(origem, destino) != 0)
    {
        std::cout << "Aresta entre " << origem << " e " << destino << " já existe!" << std::endl;
        return;
    }

    // Verifica se os índices estão dentro do limite
    if (origem > tamanhoAtual || destino > tamanhoAtual)
    {
        std::cerr << "Erro: Índices de vértice estão fora dos limites da matriz!" << std::endl;
        return;
    }

    // Para grafos direcionados
    if (eh_direcionado())
    {
        Matriz[origem - 1][destino - 1] = peso; // Adiciona a aresta na matriz de adjacência
        std::cout << "Aresta adicionada na matriz de adjacência!" << std::endl;
    }
    // Para grafos não direcionados
    else
    {
        int indice = calcularIndiceLinear(origem, destino);
        MatrizLinear[indice] = peso; // Adiciona a aresta na matriz comprimida
    }
}
